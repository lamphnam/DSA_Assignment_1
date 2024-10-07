/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   dataloader.h
 * Author: ltsach
 *
 * Created on September 2, 2024, 4:01 PM
 */

#ifndef DATALOADER_H
#define DATALOADER_H
#include "ann/xtensor_lib.h"

#include "ann/dataset.h"

#include "list/listheader.h"

using namespace std;
// template<typename DType, typename LType>

template < typename DType, typename LType >
  class DataLoader {
    public: class Iterator {
      public:

        Iterator(DataLoader & data_loader, int batch_index): data_loader(data_loader),
      batch_index(batch_index) {}

      Batch < DType,
      LType > operator * () {
        return data_loader.get_batch(batch_index);
      }

      Iterator & operator++() {
        batch_index++;
        return * this;
      }
      Iterator operator++(int) {
        Iterator tmp = * this;
        ++( * this);
        return tmp;
      }

      bool operator != (const Iterator & other) const {
        return batch_index != other.batch_index;
      }

      private: DataLoader & data_loader; // Đổi từ con trỏ thành tham chiếu
      int batch_index;
    };
    private: Dataset < DType,
    LType > * ptr_dataset;
    int batch_size;
    bool shuffle;
    bool drop_last;
    int dataset_size;
    xt::xarray < unsigned long > indices; // If shuffle = true => indices save index
    int total_batches; // Expected number of batches

    public: DataLoader(Dataset < DType, LType > * ptr_dataset,
      int batch_size,
      bool shuffle = true,
      bool drop_last = false) {
      /*TODO: Add your code to do the initialization */
      this -> ptr_dataset = ptr_dataset;
      this -> batch_size = batch_size;
      this -> shuffle = shuffle;
      this -> drop_last = drop_last;
      //this->dataset_size = ptr_dataset->len();
      //Total_batch
      dataset_size = ptr_dataset -> len();
      total_batches = dataset_size / batch_size;

      // Resize and initialize indices vector
      indices.resize({
        static_cast < size_t > (dataset_size)
      });
      for (int i = 0; i < dataset_size; i++) {
        indices[i] = i;
      }

      //Shuffle
      this -> indices = xt::arange < int > (ptr_dataset -> len());
      if (shuffle) {
        xt::random::default_engine_type engine(0);
        xt::random::shuffle(indices, engine);
      }
      // if(!shuffle) {
      //     indices = xt::arange(ptr_dataset->len());
      // }
      /*
      if (shuffle) {
          std::random_device rd;
          std::default_random_engine engine(rd());
          xt::random::shuffle(indices, engine);
      }
      */

    }
    //Get Batch    
    Batch < DType,
    LType > get_batch(int batch_index) {
      int start_index = batch_index * batch_size;
      int end_index = std::min((batch_index + 1) * batch_size, dataset_size);

      // Handle the case where drop_last is false and we're at the last batch
      if (!drop_last && batch_index == total_batches - 1) {
        end_index = dataset_size; // Include all remaining data in the last batch
      }

      int current_batch_size = end_index - start_index;

      // Check if the current batch size is valid
      if (current_batch_size <= 0) {
        throw std::runtime_error("Invalid batch size");
      }

      // Get shapes from the dataset
      auto batch_data_shape = this -> ptr_dataset -> get_data_shape();
      batch_data_shape[0] = current_batch_size; // Update batch size in data shape
      auto batch_label_shape = this -> ptr_dataset -> get_label_shape();
      batch_label_shape[0] = current_batch_size; // Update batch size in label shape

      // Create xarrays for batch data and labels
      xt::xarray < DType > batch_data = xt::empty < DType > (batch_data_shape);
      xt::xarray < LType > batch_label = xt::empty < LType > (batch_label_shape);

      // Populate the batch data and labels
      for (int i = start_index; i < end_index; ++i) {
        try {
          int index = indices[i]; // Use index from the list of indices

          DataLabel < DType, LType > data_label = ptr_dataset -> getitem(index); // Retrieve data and label

          // Retrieve data and label arrays
          auto data = data_label.getData(); // Get the data
          auto label = data_label.getLabel(); // Get the label

          // Ensure we are using the correct index to populate the batch arrays
          xt::view(batch_data, i - start_index) = data; // Store the data
          try {
            xt::view(batch_label, i - start_index) = label; // Store the label
          } catch (const std::bad_array_new_length & e) {

          }

        } catch (const std::exception & e) {
          std::cerr << "Error retrieving data for index " << indices[i] << ": " << e.what() << std::endl;
          // Handle the error appropriately; you might want to return a partial batch
          return Batch < DType, LType > (batch_data, batch_label);
        }
      }

      return Batch < DType, LType > (batch_data, batch_label); // Return the populated batch
    }

    Iterator begin() {
      return Iterator( * this, 0);
    }

    Iterator end() {
      int dataset_len = ptr_dataset -> len();
      int total_batches = (dataset_len > batch_size) ? dataset_len / batch_size : 1;
      if (dataset_len < batch_size && total_batches == 1 && drop_last) {
        total_batches = 0;
      }
      return Iterator( * this, total_batches);
    }

    virtual~DataLoader() {}

    // /////////////////////////////////////////////////////////////////////////
    // // The section for supporting the iteration and for-each to DataLoader //
    // /// START: Section                                                     //
    // /////////////////////////////////////////////////////////////////////////

    // /*TODO: Add your code here to support iteration on batch*/

    // /////////////////////////////////////////////////////////////////////////
    // // The section for supporting the iteration and for-each to DataLoader //
    // /// END: Section                                                       //
    // /////////////////////////////////////////////////////////////////////////
  };

#endif /* DATALOADER_H */