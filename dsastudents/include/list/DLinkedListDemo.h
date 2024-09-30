/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DLinkedListDemo.h
 * Author: LTSACH
 *
 * Created on 19 August 2020, 21:34
 */

#ifndef DLINKEDLISTDEMO_H
#define DLINKEDLISTDEMO_H

#include <iostream>
#include <iomanip>
#include "DLinkedList.h"
#include "../util/Point.h"
using namespace std;

void dlistDemo(){
    List<int> sample;
    for(int i = 0; i< 20; i++)
        sample.add(i, i*i);
    List<int> test1(sample);
    if(test1.toString() == "[0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361]"){
        cout << "Test 1 success" << endl;
    } else {
        cout << "Test 1 failed" << endl;
    };
    List<int> test2;
    test2 = sample;
    if(test2.toString() == "[0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361]"){
        cout << "Test 2 success" << endl;
    } else {
        cout << "Test 2 failed" << endl;
    };
    List<int> test3 = sample;
    if(test3.toString() == "[0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361]"){
        cout << "Test 3 success" << endl;
    } else {
        cout << "Test 3 failed" << endl;
    };
    List<int> test4 = sample;
    test4.add(999);
    if(test4.toString() == "[0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 999]"){
        cout << "Test 4 success" << endl;
    } else {
        cout << "Test 4 failed" << endl;
    };
    test4.add(0,-1);
    if(test4.toString() == "[-1, 0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 999]"){
        cout << "Test 5 success" << endl;
    } else {
        cout << "Test 5 failed" << endl;
    };
    test4.add(4,8);
    if(test4.toString() == "[-1, 0, 1, 4, 8, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 999]"){
        cout << "Test 6 success" << endl;
    } else {
        cout << "Test 6 failed" << endl;
    };  
}
void dlistDemo7()
{
    List<int> list;
    for (int i = 0; i < 10; i++)
        list.add(i, i * i);

    list.println();
    if (list.toString() == "[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]")
    {
        cout << "Success" << endl;
    }
    else
        cout << "Failed" << endl;

    list.add(5, 999);
    list.add(0, 123);
    list.add(1, 124);
    list.add(12, 1222);
    list.println();
    if (list.toString() == "[123, 124, 0, 1, 4, 9, 16, 999, 25, 36, 49, 64, 1222, 81]")
    {
        cout << "Success" << endl;
    }
    else
        cout << "Failed" << endl;

    list.removeAt(13);
    list.removeAt(0);
    list.removeAt(5);
    list.add(10);
    list.println();
    if (list.toString() == "[124, 0, 1, 4, 9, 999, 25, 36, 49, 64, 1222, 10]")
        cout << "Success" << endl;
    else
        cout << "Failed" << endl;

    list.removeItem(64);
    list.removeItem(90);
    list.println();
    if (list.toString() == "[124, 0, 1, 4, 9, 999, 25, 36, 49, 1222, 10]")
        cout << "Success" << endl;
    else
        cout << "Failed" << endl;

    List<int> list1 = list;
    list1.add(1);
    list1.println();
    if (list1.toString() == "[124, 0, 1, 4, 9, 999, 25, 36, 49, 1222, 10, 1]")
        cout << "Success" << endl;
    else
        cout << "Failed" << endl;

    list1 = list;
    list1.add(2);
    list1.println();
    if (list1.toString() == "[124, 0, 1, 4, 9, 999, 25, 36, 49, 1222, 10, 2]")
    {
        cout << "Success" << endl;
    }
    else
    {
        cout << "Failed" << endl;
    }

    if (!list1.contains(100))
    {
        cout << "100 not in list1" << endl;
    }
    else
        cout << "Wrong" << endl;
    if (list.contains(1222))
    {
        cout << "1222 in list1" << endl;
    }
    else
        cout << "Wrong" << endl;

    list.clear();
    list.println();
    if (list.empty())
        cout << "List is empty" << endl;
    else
        cout << "Wrong" << endl;
}
#endif /* DLINKEDLISTDEMO_H */

