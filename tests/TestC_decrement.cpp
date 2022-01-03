// This test checks whether the function list.begin() returns an decrementable
// iterator and the decrement returns again an interator

#include "testasserts.hpp"
#include <List.hpp>
#include <iostream>

int main() {
  using T = double;
  List<T> list{};
  list.push_back(1.0);
  list.push_back(2.0);
  list.push_back(3.0);

  [[maybe_unused]] auto it = list.begin(); // obtain iterator to begin

  static_assert(std::is_same<decltype(it), decltype(--it)>::value,
                "decrement does not return an iterator");
  
  ++it;
  --it;

  TEST_ASSERT(*it == 1.0, "iterator has wrong value after increment and decrement");

  return 0;
}