// This test checks whether the function list.end() returns an decrementable
// iterator and that a single decrement points to the last element

#include "testasserts.hpp"
#include <List.hpp>
#include <iostream>

int main() {
  using T = double;
  List<T> list{};
  list.push_back(1.0);
  list.push_back(2.0);
  list.push_back(3.0);

  [[maybe_unused]] auto it = list.end(); // obtain iterator to begin

  --it;

  TEST_ASSERT(*it == 3.0,
              "iterator to end not pointing to last element after decrement");

  return 0;
}
