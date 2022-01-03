// This test checks whether the iterator overloads the "member-of-pointer"
// access operator "->"

#include "testasserts.hpp"
#include <List.hpp>
#include <iostream>

struct Widget {
  double member;
};

int main() {
  using T = Widget;
  List<T> list{};
  list.push_back(Widget{1.0});
  list.push_back(Widget{2.0});
  list.push_back(Widget{3.0});

  [[maybe_unused]] auto it = list.begin(); // obtain iterator to begin

  static_assert(std::is_same<decltype(T{}.member), decltype(it->member)>::value,
                "member-of-pointer access has different type than expected");

  ++it;

  [[maybe_unused]] auto read = it->member; // read

  TEST_ASSERT(it->member == 2.0,
              "access via member-of-pointer operator reads unexpected value");

  it->member = read + 1.0; // write

  TEST_ASSERT(it->member == 3.0,
              "access via member-of-pointer operator reads unexpected value");

  return 0;
}