#include <catch2/catch.hpp>

TEST_CASE("Memory leak test-case") {
  auto arr = new int[5]{};  // allocated and not deallocated
}

TEST_CASE("Memory freed test-case") {
  auto arr = new int[5]{};  // allocated
  delete[] arr;             // deallocated
}