/*
 * File:   DLinkedList.h
 */

#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include "IList.h"

#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;

template<class T>
class DLinkedList : public IList<T> {
public:
    class Node; // Forward declaration
    class Iterator; // Forward declaration
    class BWDIterator; // Forward declaration

protected:
    Node *head; // this node does not contain user's data
    Node *tail; // this node does not contain user's data
    int count;

    bool (*itemEqual)(T &lhs, T &rhs); // function pointer: test if two items (type: T&) are equal or not
    void (*deleteUserData)(DLinkedList<T> *); // function pointer: be called to remove items (if they are pointer type)

public:
    DLinkedList(
        void (*deleteUserData)(DLinkedList<T> *) = 0,
        bool (*itemEqual)(T &, T &) = 0);

    DLinkedList(const DLinkedList<T> &list);

    DLinkedList<T> &operator=(const DLinkedList<T> &list);

    ~DLinkedList();

    // Inherit from IList: BEGIN
    void add(T e);

    void add(int index, T e);

    T removeAt(int index);

    bool removeItem(T item, void (*removeItemData)(T) = 0);

    bool empty();

    int size();

    void clear();

    T &get(int index);

    int indexOf(T item);

    bool contains(T item);

    string toString(string (*item2str)(T &) = 0);

    // Inherit from IList: END

    void println(string (*item2str)(T &) = 0) {
        cout << toString(item2str) << endl;
    }

    void setDeleteUserDataPtr(void (*deleteUserData)(DLinkedList<T> *) = 0) {
        this->deleteUserData = deleteUserData;
    }

    bool contains(T array[], int size) {
        int idx = 0;
        for (DLinkedList<T>::Iterator it = begin(); it != end(); it++) {
            if (!equals(*it, array[idx++], this->itemEqual))
                return false;
        }
        return true;
    }

    /*
     * free(DLinkedList<T> *list):
     *  + to remove user's data (type T, must be a pointer type, e.g.: int*, Point*)
     *  + if users want a DLinkedList removing their data,
     *      he/she must pass "free" to constructor of DLinkedList
     *      Example:
     *      DLinkedList<T> list(&DLinkedList<T>::free);
     */
    static void free(DLinkedList<T> *list) {
        typename DLinkedList<T>::Iterator it = list->begin();
        while (it != list->end()) {
            delete *it;
            it++;
        }
    }

    /* begin, end and Iterator helps user to traverse a list forwardly
     * Example: assume "list" is object of DLinkedList

     DLinkedList<char>::Iterator it;
     for(it = list.begin(); it != list.end(); it++){
            char item = *it;
            std::cout << item; //print the item
     }
     */
    Iterator begin() {
        return Iterator(this, true);
    }

    Iterator end() {
        return Iterator(this, false);
    }

    /* last, beforeFirst and BWDIterator helps user to traverse a list backwardly
     * Example: assume "list" is object of DLinkedList

     DLinkedList<char>::BWDIterator it;
     for(it = list.last(); it != list.beforeFirst(); it--){
            char item = *it;
            std::cout << item; //print the item
     }
     */
    BWDIterator bbegin() {
        return BWDIterator(this, true);
    }

    BWDIterator bend() {
        return BWDIterator(this, false);
    }

protected:
    static bool equals(T &lhs, T &rhs, bool (*itemEqual)(T &, T &)) {
        if (itemEqual == 0)
            return lhs == rhs;
        else
            return itemEqual(lhs, rhs);
    }

    void copyFrom(const DLinkedList<T> &list);

    void removeInternalData();

    Node *getPreviousNodeOf(int index);

    //////////////////////////////////////////////////////////////////////
    ////////////////////////  INNER CLASSES DEFNITION ////////////////////
    //////////////////////////////////////////////////////////////////////
public:
    class Node {
    public:
        T data;
        Node *next;
        Node *prev;
        friend class DLinkedList<T>;

    public:
        Node(Node *next = 0, Node *prev = 0) {
            this->next = next;
            this->prev = prev;
        }

        Node(T data, Node *next = 0, Node *prev = 0) {
            this->data = data;
            this->next = next;
            this->prev = prev;
        }
    };

    //////////////////////////////////////////////////////////////////////
    class Iterator {
    private:
        DLinkedList<T> *pList;
        Node *pNode;

    public:
        Iterator(DLinkedList<T> *pList = 0, bool begin = true) {
            if (begin) {
                if (pList != 0)
                    this->pNode = pList->head->next;
                else
                    pNode = 0;
            } else {
                if (pList != 0)
                    this->pNode = pList->tail;
                else
                    pNode = 0;
            }
            this->pList = pList;
        }

        Iterator &operator=(const Iterator &iterator) {
            this->pNode = iterator.pNode;
            this->pList = iterator.pList;
            return *this;
        }

        void remove(void (*removeItemData)(T) = 0) {
            pNode->prev->next = pNode->next;
            pNode->next->prev = pNode->prev;
            Node *pNext = pNode->prev; // MUST prev, so iterator++ will go to end
            if (removeItemData != 0)
                removeItemData(pNode->data);
            delete pNode;
            pNode = pNext;
            pList->count -= 1;
        }

        T &operator*() {
            return pNode->data;
        }

        bool operator!=(const Iterator &iterator) {
            return pNode != iterator.pNode;
        }

        // Prefix ++ overload
        Iterator &operator++() {
            pNode = pNode->next;
            return *this;
        }

        // Postfix ++ overload
        Iterator operator++(int) {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }
    };
};

//////////////////////////////////////////////////////////////////////
// Define a shorter name for DLinkedList:

template<class T>
using List = DLinkedList<T>;

//////////////////////////////////////////////////////////////////////
////////////////////////     METHOD DEFNITION      ///////////////////
//////////////////////////////////////////////////////////////////////

template<class T>
DLinkedList<T>::DLinkedList(
    void (*deleteUserData)(DLinkedList<T> *),
    bool (*itemEqual)(T &, T &)) {
    this->deleteUserData = deleteUserData;
    this->itemEqual = itemEqual;

    head = new Node();
    tail = new Node();

    head->next = tail;
    tail->prev = head;

    count = 0;
}

template<class T>
DLinkedList<T>::DLinkedList(const DLinkedList<T> &list) {
    // TODO
    // Gán các hàm con trỏ từ danh sách cũ
    this->deleteUserData = list.deleteUserData;
    this->itemEqual = list.itemEqual;

    // Tạo nút đầu và nút đuôi mới
    head = new Node();
    tail = new Node();

    head->next = tail;
    tail->prev = head;

    count = 0; // Khởi tạo số lượng mục bằng 0

    // Sao chép từng nút từ danh sách cũ
    Node *current = list.head->next; // Bắt đầu từ nút đầu thực sự
    while (current != list.tail) {
        // Lặp cho đến khi gặp nút đuôi
        add(current->data); // Sử dụng phương thức add để thêm dữ liệu vào danh sách mới
        current = current->next; // Di chuyển đến nút tiếp theo
    }
}

template<class T>
DLinkedList<T> &DLinkedList<T>::operator=(const DLinkedList<T> &list) {
    if (this != &list) {
        // Kiểm tra xem có phải gán chính nó không
        clear(); // Xóa danh sách hiện tại để tránh rò rỉ bộ nhớ

        // Gán các hàm con trỏ
        this->deleteUserData = list.deleteUserData;
        this->itemEqual = list.itemEqual;

        // Tạo nút đầu và nút đuôi mới
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
        count = 0;

        // Sao chép dữ liệu từ danh sách cũ
        Node *current = list.head->next; // Bắt đầu từ nút đầu thực sự
        while (current != list.tail) {
            add(current->data); // Sử dụng phương thức add để thêm dữ liệu
            current = current->next; // Di chuyển đến nút tiếp theo
        }
    }
    return *this; // Trả về tham chiếu đến danh sách hiện tại
}

template<class T>
DLinkedList<T>::~DLinkedList() {
    clear(); // Gọi phương thức clear để xóa tất cả các mục
    delete head; // Giải phóng bộ nhớ cho nút đầu
    delete tail; // Giải phóng bộ nhớ cho nút đuôi
}

template<class T>
void DLinkedList<T>::add(T e) {
    // TODO
    Node *newNode = new Node(e);

    newNode->prev = tail->prev;
    newNode->next = tail;
    tail->prev->next = newNode;
    tail->prev = newNode;
    count++;
}

template<class T>
void DLinkedList<T>::add(int index, T e) {
    if (index < 0 || index > count) {
        throw out_of_range("Index is out of range.");
    }

    Node *newNode = new Node(e);

    if (index == count) { // Thêm vào cuối danh sách
        newNode->prev = tail->prev;
        newNode->next = tail;
        tail->prev->next = newNode;
        tail->prev = newNode;
    } else {
        Node *current = getPreviousNodeOf(index);
        newNode->next = current->next; // Cập nhật next của newNode
        newNode->prev = current; // Cập nhật prev của newNode

        if (current->next != nullptr) {
            current->next->prev = newNode; // Cập nhật prev của nút tiếp theo
        }
        current->next = newNode; // Cập nhật next của current
    }

    count++; // Tăng số lượng mục trong danh sách
}

template<class T>
typename DLinkedList<T>::Node *DLinkedList<T>::getPreviousNodeOf(int index) {
    if (index < 0 || index > count) {
        throw out_of_range("Index is out of range.");
    }

    Node *current = head; // Bắt đầu từ nút đầu

    for (int i = 0; i < index; ++i) {
        current = current->next; // Di chuyển tới nút tiếp theo
    }

    return current; // Trả về nút trước chỉ số
}


template<class T>
T DLinkedList<T>::removeAt(int index) {
    if (index < 0 || index >= count) {
        throw out_of_range("Index is out of range.");
    }

    Node* current = getPreviousNodeOf(index + 1);
    T data = current->data;

    // Cập nhật các con trỏ nếu current không phải là nút đầu hoặc nút cuối
    if (current->prev != nullptr) {
        current->prev->next = current->next;
    }
    if (current->next != nullptr) {
        current->next->prev = current->prev;
    }

    delete current; // Giải phóng bộ nhớ cho nút hiện tại

    count--; // Giảm số lượng phần tử

    return data; // Trả về dữ liệu của nút đã xóa
}


template<class T>
bool DLinkedList<T>::empty() {
    // TODO
    return count == 0;
}

template<class T>
int DLinkedList<T>::size() {
    // TODO
    return count;
}

template<class T>
void DLinkedList<T>::clear() {
    if (head == nullptr || tail == nullptr) {
        return; // Danh sách đã rỗng hoặc không hợp lệ
    }

    Node* current = head->next;

    while (current != tail) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }

    head->next = tail;
    tail->prev = head;
    count = 0;
}


template<class T>
T &DLinkedList<T>::get(int index) {
    if (index < 0 || index >= count) {
        throw out_of_range("Index is out of range."); // Kiểm tra chỉ số hợp lệ
    }

    Node* current = getPreviousNodeOf(index + 1); // Lấy nút tại vị trí chỉ định
    return current->data; // Trả về dữ liệu của nút
}


template <typename T>
int DLinkedList<T>::indexOf(T value) {
    Node* current = head;
    int index = 0;

    while (current != nullptr) {
        if (current->data == value) { // Assuming T has an operator==
            return index; // Found the value
        }
        current = current->next;
        index++;
    }
    return -1; // Return -1 if not found
}

template<class T>
bool DLinkedList<T>::removeItem(T item, void (*removeItemData)(T)) {
    Iterator it = begin(); // Bắt đầu từ đầu danh sách

    while (it != end()) { // Duyệt qua tất cả các phần tử
        if (equals(*it, item, this->itemEqual)) { // Kiểm tra xem phần tử có bằng với item không
            it.remove(removeItemData); // Xóa phần tử hiện tại
            return true; // Trả về true nếu xóa thành công
        }
        ++it; // Tiến tới phần tử tiếp theo
    }

    return false; // Trả về false nếu không tìm thấy phần tử để xóa
}


template<class T>
bool DLinkedList<T>::contains(T item) {
    Iterator it = begin(); // Bắt đầu từ đầu danh sách

    while (it != end()) { // Duyệt qua tất cả các phần tử
        if (equals(*it, item, this->itemEqual)) { // Kiểm tra xem phần tử có bằng với item không
            return true; // Trả về true nếu tìm thấy phần tử
        }
        ++it; // Tiến tới phần tử tiếp theo
    }

    return false; // Trả về false nếu không tìm thấy phần tử
}


template<class T>
string DLinkedList<T>::toString(string (*item2str)(T &)) {
    if (head == nullptr || tail == nullptr) {
        return "[]"; // Danh sách rỗng
    }

    stringstream ss;
    Node *current = head->next; // Bắt đầu từ nút đầu tiên

    ss << "[";
    while (current != tail) { // Duyệt qua danh sách
        if (item2str != nullptr) {
            ss << item2str(current->data); // Sử dụng hàm tùy chỉnh để chuyển đổi
        } else {
            ss << current->data; // Sử dụng toán tử stream mặc định cho kiểu T
        }

        current = current->next;
        if (current != tail) {
            ss << ", "; // Thêm dấu phân cách giữa các mục
        }
    }
    ss << "]";

    return ss.str();
}

template<class T>
void DLinkedList<T>::copyFrom(const DLinkedList<T> &list) {
    // Xóa nội dung hiện tại để đảm bảo danh sách trống
    clear();

    // Kiểm tra nếu danh sách nguồn không rỗng
    if (list.empty()) {
        return; // Nếu danh sách nguồn trống, không cần làm gì thêm
    }

    // Duyệt qua danh sách nguồn và thêm từng phần tử vào danh sách hiện tại
    for (Iterator it = list.begin(); it != list.end(); ++it) {
        add(*it); // Thêm phần tử vào danh sách hiện tại
    }
}


template<class T>
void DLinkedList<T>::removeInternalData() {
    Node *current = head->next; // Bắt đầu từ nút đầu tiên (sau nút đầu)
    while (current != tail) { // Duyệt đến nút trước nút cuối
        Node *nextNode = current->next; // Lưu trữ nút tiếp theo
        if (deleteUserData) { // Kiểm tra xem có hàm xóa dữ liệu người dùng không
            deleteUserData(current); // Gọi hàm xóa nếu có
        }
        delete current; // Xóa nút hiện tại
        current = nextNode; // Di chuyển đến nút tiếp theo
    }
    head->next = tail; // Đặt lại con trỏ của nút đầu
    tail->prev = head; // Đặt lại con trỏ của nút cuối
    count = 0; // Đặt lại số lượng phần tử
}


#endif /* DLINKEDLIST_H */
