#include "assignment/code.hpp"

#include <iostream>   // cout, printf
#include <algorithm>  // fill, copy

namespace assignment {

  // Task 1
  int squared_diff(int left, int right) {
    int sqr = left - right;
    sqr = sqr * sqr;
    return sqr;
  }

  // Task 2
  bool check_bit(int mask, int bit_pos) {
    if (mask < 0 || bit_pos < 0) {
        return false;
    }
    int count = -1;
    int num = mask;
    int ost = 0;
    int var = 0;
    while (num != 0) {
      ost = num % 2;
      num = num / 2;
      count ++;
      if (count == bit_pos) {
          var = ost;
          if (var == 1){
            return true;
          }
        }
    }

    return false;
  }

  // Task 3
  int max3(int left, int middle, int right) {
    int max;
    if (left >= middle && left >= right){
      max = left;
    }
    if (middle >= left && middle >= right){
      max = middle;
    }
    if (right >= left && right >= middle){
      max = right;
    }


    return max;
  }

  // Task 4
  void swap_args(int* left, int* right) {
    if (!(left == nullptr || right == nullptr)){
      int t = *left;
      *left = *right;
      *right = t;
    }

  }

  // Task 5
  int arr_sum(int* arr, int length) {
    if (arr == nullptr || length <= 0){
      return 0;
    }
    int sum = 0;
    for (int i=0; i < length; i++) {
      sum += arr[i];
    }

    return sum;
  }

  // Task 6
  int *find_max_elem(int* arr, int length) {
    if (arr == nullptr || length <= 0){
      return nullptr;
    }
    int max = arr[0];
    int* pointer_max = &arr[0];
    for (int i = 1; i < length; i++){
      if (arr[i] > max) {
          max = arr[i];
          pointer_max = &arr[i];
        }
    }

    return pointer_max;
  }

  // Task 7
  int *allocate_arr(int length, int init_value) {
    if (length <= 0){
      return nullptr;
    }
    int* arr = new int[length];
    std::fill(arr, arr+length, init_value);

    return arr;
  }

  // Task 8
  int *clone_arr(int* arr_in, int length) {
    if (arr_in == nullptr || length <= 0){
      return nullptr;
    }
    int* arr = new int[length];
    std::copy(arr_in, arr_in + length, arr);

    return arr;
  }

  // Task 9
  void print_kth_elements(int* arr, int length, int k, std::ostream &os) {
    if (arr == nullptr){
      os << "Invalid argument: arr\n";
    }
    else if (length <= 0){
      os << "Invalid argument: length\n";
    }
    else if (k <= 0){
      os << "Invalid argument: k\n";
    }
    else{
      for(int i=0; i<length; i+=k){
        os << arr[i]<< '\t';
      }
    }
  }

}  // namespace assignment
