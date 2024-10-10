#include "ann/funtions.h"
#include "ann/xtensor_lib.h"
#include "ann/dataset.h"
#include "ann/dataloader.h"
#include "list/XArrayListDemo.h"
#include "list/XArrayList.h"
#include "include/list/DLinkedList.h"
#include "include/list/DLinkedListDemo.h"
#include "include/ann/DataLoaderDemo.h"
#include <iostream>

using namespace std;

// !compile: g++ -Iinclude -std=c++17 main.cpp -o output_program

int main(int argc, char **argv) {
    case_data_wi_label_1();
    //case_data_wo_label_1();
    case_data_wo_label_2();
    
    return 0;
}   