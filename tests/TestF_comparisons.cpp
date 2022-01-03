// This test checks whether the iterator supports comparisons

#include "testasserts.hpp"
#include <List.hpp>
#include <iostream>

int main() {
  using T = double;

  static_assert(
      std::is_same<decltype(List<T>{}.begin() != List<T>{}.end()), bool>::value,
      "comparison using != does not return a bool");
  static_assert(
      std::is_same<decltype(List<T>{}.begin() == List<T>{}.end()), bool>::value,
      "comparison using == does not return a bool");

  { // empty list, expecting begin == end
    List<T> list{};
    [[maybe_unused]] auto begin = list.begin(); // obtain iterator to begin
    [[maybe_unused]] auto end = list.end();     // obtain iterator to end
    TEST_ASSERT(begin == end, "begin() is not eqaul to end() for empty list");
  }

  { // non-empty list, expecting begin != end
    List<T> list{};
    list.push_back(42.0);
    [[maybe_unused]] auto begin = list.begin(); // obtain iterator to begin
    [[maybe_unused]] auto end = list.end();     // obtain iterator to end
    TEST_ASSERT(begin != end, "begin() is equal to end() for non-empty list");
  }

  return 0;
}