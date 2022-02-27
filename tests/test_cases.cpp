#include <catch2/catch.hpp>

#include <algorithm>  // max_element
#include <cmath>      // pow, max
#include <iterator>   // next
#include <memory>     // unique_ptr
#include <numeric>    // accumulate
#include <sstream>    // stringstream
#include <vector>

#include "utils.hpp"  // rand_array

#include "assignment/code.hpp"

using namespace Catch;
using namespace assignment;

SCENARIO("squared difference") {

  GIVEN("2 integers") {
    const int left = GENERATE(range(-10, 10));
    const int right = GENERATE(range(-10, 10));

    WHEN("computing squared difference") {
      const int diff = squared_diff(left, right);
      const auto ref_diff = static_cast<int>(std::pow(left - right, 2));

      THEN("it should be equal to the correct value") {
        CAPTURE(left, right, diff);
        CHECK(diff == ref_diff);
      }
    }
  }
}

SCENARIO("check bit position") {

  GIVEN("mask with a single bit set") {
    const int max_pos = 11;
    const int bit_pos_ref = GENERATE_COPY(range(0, max_pos));

    const int mask = 1 << bit_pos_ref;  // 1, 10, 100, ...

    WHEN("checking bit at set position") {
      const auto pred = [&bit_pos_ref](int pos) { return pos == bit_pos_ref; };
      const int bit_pos = GENERATE_REF(filter(pred, range(0, max_pos)));

      THEN("it should return true") {
        CAPTURE(mask, bit_pos);
        CHECK(check_bit(mask, bit_pos));
      }
    }

    AND_WHEN("checking bit at non-set position") {
      const auto pred = [&bit_pos_ref](int pos) { return pos != bit_pos_ref; };
      const int bit_pos = GENERATE_REF(filter(pred, range(0, max_pos)));

      THEN("it should return false") {
        CAPTURE(mask, bit_pos);
        CHECK_FALSE(check_bit(mask, bit_pos));
      }
    }
  }

  AND_GIVEN("negative mask") {
    const int mask = GENERATE(range(-5, 0));

    WHEN("checking the bit at any position") {
      const int bit_pos = GENERATE(range(0, 5));

      THEN("it should return false") {
        CHECK_FALSE(check_bit(mask, bit_pos));
      }
    }
  }
}

SCENARIO("find max element") {

  GIVEN("three elements") {
    const int trial = GENERATE(range(0, 100));
    const auto elems = utils::rand_array(3, -100, 100, true);

    WHEN("finding max element") {
      const int max_elem = max3(elems[0], elems[1], elems[2]);
      const int max_elem_ref = *std::max_element(elems.cbegin(), elems.cend());

      THEN("it should be correct") {
        CAPTURE(trial, elems, max_elem);
        CHECK(max_elem == max_elem_ref);
      }
    }
  }
}

SCENARIO("swap argument values") {

  GIVEN("two different variables") {
    const int trial = GENERATE(range(0, 100));
    const auto elems = utils::rand_array(2, -100, 100, true);

    int left = elems[0];
    int right = elems[1];

    WHEN("swapping values") {
      swap_args(&left, &right);

      THEN("values should be swapped") {
        CAPTURE(trial, elems);
        CHECK(left == elems[1]);
        CHECK(right == elems[0]);
      }
    }
  }

  AND_GIVEN("one of variables is nullptr") {
    int* left = nullptr;
    int right = GENERATE(take(100, random(-1000, 1000)));

    WHEN("swapping nullptr with variable") {
      const int prev_var = right;
      swap_args(left, &right);

      THEN("variable should have the same value") {
        CAPTURE(left, right);
        CHECK(right == prev_var);
      }
    }

    AND_WHEN("swapping variable with nullptr") {
      const int prev_var = right;
      swap_args(&right, left);

      THEN("variable should have the same value") {
        CAPTURE(left, right);
        CHECK(right == prev_var);
      }
    }
  }
}

SCENARIO("sum of array elements") {

  GIVEN("array of elements") {
    const int length = GENERATE(range(1, 50));
    auto arr = utils::rand_array(length, -100, 100);

    WHEN("computing the sum of elements") {
      const int sum = arr_sum(arr.data(), length);
      const int sum_ref = std::accumulate(arr.cbegin(), arr.cend(), 0);

      THEN("it should match the correct value") {
        CAPTURE(arr, length);
        CHECK(sum == sum_ref);
      }
    }
  }

  AND_GIVEN("nullptr array pointer") {
    int* arr = nullptr;
    const int length = GENERATE(range(1, 10));

    WHEN("computing the sum of elements") {
      const int sum = arr_sum(arr, length);

      THEN("it should return zero") {
        CAPTURE(arr, length);
        CHECK(sum == 0);
      }
    }
  }

  AND_GIVEN("non-positive array length") {
    const int length = GENERATE(range(-10, 1));
    auto arr = utils::rand_array(5, -100, 100);

    WHEN("computing the sum of elements") {
      const int sum = arr_sum(arr.data(), length);

      THEN("it should return zero") {
        CAPTURE(arr, length);
        CHECK(sum == 0);
      }
    }
  }
}

SCENARIO("find max array element") {

  GIVEN("array of elements") {
    const int length = GENERATE(range(1, 50));
    auto arr = utils::rand_array(length, -1000, 1000);

    WHEN("finding max element") {
      int* max_elem = find_max_elem(arr.data(), length);
      const auto max_elem_ref = std::max_element(arr.cbegin(), arr.cend());

      THEN("it should return correct pointer") {
        CAPTURE(arr, length);
        CHECK(max_elem == &(*max_elem_ref));
      }
    }
  }

  AND_GIVEN("nullptr array pointer") {
    int* arr = nullptr;
    const int length = GENERATE(range(1, 10));

    WHEN("finding max element") {
      int* max_elem = find_max_elem(arr, length);

      THEN("it should return nullptr") {
        CAPTURE(arr, length);
        CHECK(max_elem == nullptr);
      }
    }
  }

  AND_GIVEN("non-positive array length") {
    const int length = GENERATE(range(-10, 1));
    auto arr = utils::rand_array(5, -1000, 1000);

    WHEN("finding max element") {
      int* max_elem = find_max_elem(arr.data(), length);

      THEN("it should return nullptr") {
        CAPTURE(arr, length);
        CHECK(max_elem == nullptr);
      }
    }
  }
}

SCENARIO("allocate array") {

  GIVEN("positive length") {
    const int length = GENERATE(range(1, 50));
    const int init_value = GENERATE(take(10, random(-100, 100)));

    WHEN("allocating array") {
      std::unique_ptr<int[]> arr(allocate_arr(length, init_value));

      THEN("it should be created and initialized") {
        CAPTURE(arr, length);
        REQUIRE(arr != nullptr);

        const auto vec = std::vector<int>(arr.get(), arr.get() + length);
        const auto vec_ref = std::vector<int>(length, init_value);
        CHECK_THAT(vec, Matchers::Equals(vec_ref));
      }
    }
  }

  AND_GIVEN("non-positive length") {
    const int length = GENERATE(range(-10, 1));
    const int init_value = GENERATE(take(10, random(-100, 100)));

    WHEN("allocating array") {
      std::unique_ptr<int[]> arr(allocate_arr(length, init_value));

      THEN("it should return nullptr") {
        CAPTURE(arr, length);
        CHECK(arr == nullptr);
      }
    }
  }
}

SCENARIO("clone array") {

  GIVEN("array of elements") {
    const int length = GENERATE(range(1, 10));
    auto arr = utils::rand_array(length, -100, 100);

    WHEN("cloning array") {
      auto clone = std::unique_ptr<int[]>(clone_arr(arr.data(), length));

      THEN("it should return nullptr") {
        CAPTURE(arr, length);
        REQUIRE(clone != nullptr);

        const auto vec = std::vector<int>(clone.get(), clone.get() + length);
        CHECK_THAT(vec, Matchers::Equals(arr));
      }
    }
  }

  AND_GIVEN("nullptr pointer to array") {
    int* arr = nullptr;
    const int length = GENERATE(range(1, 10));

    WHEN("cloning array") {
      auto clone = std::unique_ptr<int[]>(clone_arr(arr, length));

      THEN("it should return nullptr") {
        CAPTURE(arr, length);
        CHECK(clone == nullptr);
      }
    }
  }

  AND_GIVEN("non-positive length") {
    const int length = GENERATE(range(-10, 1));
    auto arr = utils::rand_array(5, -100, 100);

    WHEN("cloning array") {
      auto clone = std::unique_ptr<int[]>(clone_arr(arr.data(), length));

      THEN("it should return nullptr") {
        CAPTURE(arr, length);
        CHECK(clone == nullptr);
      }
    }
  }
}

SCENARIO("print every kth array element") {

  GIVEN("k is less than or equals to array length") {
    const int length = GENERATE(range(2, 10));
    auto arr = utils::rand_array(length, -100, 100);

    const int k = GENERATE_REF(range(1, length + 1));

    WHEN("printing every kth element") {
      std::stringstream ss;
      print_kth_elements(arr.data(), length, k, ss);

      std::stringstream ss_ref;

      for (auto it = arr.begin();; it = std::next(it, k)) {
        ss_ref << *it << '\t';
        if (std::distance(it, arr.end()) <= k) {
          break;
        }
      }

      THEN("output should contain every kth element") {
        CAPTURE(arr, length, k);
        CHECK_THAT(ss.str(), Matchers::Equals(ss_ref.str()));
      }
    }
  }

  AND_GIVEN("k is greater than array length") {
    const int length = GENERATE(range(1, 10));
    auto arr = utils::rand_array(length, -100, 100);

    const int k = GENERATE_REF(range(length + 1, length + 10));

    WHEN("printing every kth element") {
      std::stringstream ss;
      print_kth_elements(arr.data(), length, k, ss);

      THEN("output should contain the 1st element") {
        CAPTURE(arr, length, k);
        CHECK_THAT(ss.str(), Matchers::Equals(std::to_string(arr[0]) + '\t'));
      }
    }
  }

  AND_GIVEN("k is non-positive") {
    const int length = GENERATE(range(1, 10));
    auto arr = utils::rand_array(length, -100, 100);

    const int k = GENERATE(range(-10, 1));

    WHEN("printing every kth element") {
      std::stringstream ss;
      print_kth_elements(arr.data(), length, k, ss);

      THEN("output should contain invalid k message") {
        CAPTURE(arr, length, k);
        CHECK_THAT(ss.str(), Matchers::Contains("Invalid argument: k"));
      }
    }
  }

  AND_GIVEN("nullptr array") {
    const int length = GENERATE(range(1, 10));
    const int k = GENERATE(range(1, 5));

    int* arr = nullptr;

    WHEN("printing every kth element") {
      std::stringstream ss;
      print_kth_elements(arr, length, k, ss);

      THEN("output should contain invalid array message") {
        CAPTURE(arr, length, k);
        CHECK_THAT(ss.str(), Matchers::Contains("Invalid argument: arr"));
      }
    }
  }

  AND_GIVEN("non-positive array length") {
    const int length = GENERATE(range(-10, 1));
    const int k = GENERATE(range(1, 5));

    auto arr = utils::rand_array(5, -100, 100);

    WHEN("printing every kth element") {
      std::stringstream ss;
      print_kth_elements(arr.data(), length, k, ss);

      THEN("output should contain invalid length message") {
        CAPTURE(arr, length, k);
        CHECK_THAT(ss.str(), Matchers::Contains("Invalid argument: length"));
      }
    }
  }
}