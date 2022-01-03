// This test checks whether the iterator supports comparisons

#include "testasserts.hpp"
#include <List.hpp>
#include <iostream>
#include <string>

int main() {
  using T = double;

  { // explicit for loop
    List<T> list{};
    for (const auto &value : {1, 2, 3, 4, 5}) {
      list.push_back(value);
    }
    int count = 1;
    for (auto it = list.begin(); it != list.end(); ++it) {
      TEST_ASSERT(*it == count++,
                  "value access in for loop not matching expectations");
    }
  }
  { // range-based for loop
    List<T> list{};
    for (const auto &value : {1, 2, 3, 4, 5}) {
      list.push_back(value);
    }
    int count = 1;
    for (const auto& item : list) {
      TEST_ASSERT(item == count++,
                  "value access in range-based loop not matching expectations");
    }
  }
  { // while loop
    List<T> list{};
    for (const auto &value : {1, 2, 3, 4, 5}) {
      list.push_back(value);
    }
    auto it = list.begin();
    int count = 1;
    while (it != list.end()) {
      TEST_ASSERT(*it == count++,
                  "value access in while loop not matching expectations");
      ++it;
    }
  }

  return 0;
}