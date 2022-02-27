#pragma once

#include <iostream>  // cout, ostream

namespace assignment {

  int squared_diff(int left, int right);

  bool check_bit(int mask, int bit_pos);

  int max3(int left, int middle, int right);

  void swap_args(int* left, int* right);

  int arr_sum(int* arr, int length);

  int* find_max_elem(int* arr, int length);

  int* allocate_arr(int length, int init_value);

  int* clone_arr(int* arr_in, int length);

  void print_kth_elements(int* arr, int length, int k, std::ostream& os = std::cout);

}  // namespace assignment
