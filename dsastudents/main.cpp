#include "ann/funtions.h"
#include "ann/xtensor_lib.h"
#include "ann/dataset.h"
#include "ann/dataloader.h"
#include "list/XArrayListDemo.h"
#include "list/XArrayList.h"
#include "include/list/DLinkedList.h"
#include "include/list/DLinkedListDemo.h"
#include <iostream>

using namespace std;

void dataloadertc3(){
    xt::random::seed(10);
    xt::xarray<double> X = xt::random::randn<double>({105, 10, 10});
    xt::xarray<int> t = xt::ones<int>({105});
    TensorDataset<double, int> ds(X, t);
    DataLoader<double, int> loader(&ds, 10, false);
    auto it = loader.begin();
    it++;
    cout << xt::adapt((*it).getData().shape()) << endl;
    cout << xt::adapt((*it).getLabel().shape()) << endl;
    cout << xt::adapt((*(++it)).getData().shape()) << endl;
    cout << xt::adapt((*(++it)).getLabel().shape()) << endl;
}

void dataloadertc6(){
    xt::random::seed(10);
    xt::xarray<double> X = xt::random::randn<double>({100, 3, 3});
    xt::xarray<int> t = xt::ones<int>({100});
    TensorDataset<double, int> ds(X, t);
    DataLoader<double, int> loader(&ds, 10, false, true);
    for(auto batch: loader){
        cout << batch.getData() << endl;
        cout << batch.getLabel() << endl;
    }
}


int main(int argc, char **argv) {
    dataloadertc3();
    dataloadertc6();
    
    return 0;
}   