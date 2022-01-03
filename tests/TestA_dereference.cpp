//  This test checks, whether the function list.begin() returns a dereferencable
//  iterator which allows to read and write the value

#include "testasserts.hpp"
#include <List.hpp>
#include <iostream>

int main() {
  using T = double;
  List<T> list{};
  list.push_back(3.1415);

  [[maybe_unused]] auto it = list.begin(); // obtain iterator to begin

  static_assert(std::is_same<T &, decltype(*it)>::value,
                "dereferencing does not result in reference to T");

  TEST_ASSERT(*it == 3.1415, "iterator to begin has wrong value");

  *it = 3.0; // writing value via iterator return value

  TEST_ASSERT(*it == 3.0,
              "writing via return value of iterator not working as expected");

  return 0;
}