#pragma once

#include <vector>
#include <random>
#include <unordered_set>
#include <algorithm>  // generate, shuffle

namespace utils {

  inline std::vector<int> rand_array(int length, int start, int end, bool unique = false) {
    auto engine = std::mt19937(std::random_device{}());
    auto dist = std::uniform_int_distribution<>(start, end);

    auto arr = std::vector<int>(length);
    auto unique_arr = std::unordered_set<int>(length);

    if (unique) {
      while (unique_arr.size() < length) {
        const int elem = dist(engine);

        if (unique_arr.count(elem) == 0) {
          unique_arr.insert(elem);
        }
      }

      arr.assign(unique_arr.cbegin(), unique_arr.cend());

    } else {
      std::generate(arr.begin(), arr.end(), [&dist, &engine]() { return dist(engine); });
    }

    std::shuffle(arr.begin(), arr.end(), engine);
    return arr;
  }

}  // namespace utils
