#include "ann/funtions.h"
#include "ann/xtensor_lib.h"
#include "ann/dataset.h"
#include "ann/dataloader.h"

#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    int nsamples = 100;
    xt ::xarray<double> X = xt ::random ::randn<double>({nsamples, 10});
    xt ::xarray<double> T = xt ::random ::randn<double>({nsamples, 5});
    TensorDataset<double, double> ds(X, T);
    // DataLoader<double, double> loader(&ds, 30, true, false);
    cout << "len: " << ds.len() << endl; // In ra số lượng mẫu
    cout << "Data shape: " << shape2str(ds.get_data_shape()) << endl; // In ra shape của data
    cout << "Label shape: " << shape2str(ds.get_label_shape()) << endl; // In ra shape của label
    // for (auto batch : loader) {
    // cout << shape2str(batch.getData().shape()) << endl;
    // cout << shape2str(batch.getLabel().shape()) << endl;
    // }
    return 0;
}