// This test checks, whether the iterators returned are stdlib conformal and can
// be used with stdlib functions.

// Check the nested member types for an iterator required for stdlib
// conformality: https://en.cppreference.com/w/cpp/iterator/iterator_traits:
// using value_type = /* TODO */;
// using iterator_category = /* TODO */;
// using difference_type = /* TODO */;
// using pointer = /* TODO */;
// using reference = /* TODO */;

#include "testasserts.hpp"
#include <List.hpp>
#include <algorithm>
#include <iostream>
#include <string>
#include <type_traits>

int main() {
  using T = double;

  { // check nested types of iterator

    // List::iterator

    static_assert(std::is_same<List<T>::iterator::value_type, T>::value,
                  "iterator::value_type has unexpected type");
    static_assert(std::is_same<List<T>::iterator::iterator_category,
                               std::bidirectional_iterator_tag>::value,
                  "iterator::iterator_category has unexpected type");
    static_assert(
        std::is_same<List<T>::iterator::difference_type, std::ptrdiff_t>::value,
        "iterator::difference_type has unexpected type");
    static_assert(std::is_same<List<T>::iterator::pointer, T *>::value,
                  "iterator::pointer has unexpected type");
    static_assert(std::is_same<List<T>::iterator::reference, T &>::value,
                  "iterator::reference has unexpected type");

    // List::const_iterator

    static_assert(
        std::is_same<List<T>::const_iterator::value_type, const T>::value,
        "const_iterator::value_type has unexpected type");
    static_assert(std::is_same<List<T>::const_iterator::iterator_category,
                               std::bidirectional_iterator_tag>::value,
                  "const_iterator::iterator_category has unexpected type");
    static_assert(std::is_same<List<T>::const_iterator::difference_type,
                               std::ptrdiff_t>::value,
                  "const_iterator::difference_type has unexpected type");
    static_assert(
        std::is_same<List<T>::const_iterator::pointer, const T *>::value,
        "const_iterator::pointer has unexpected type");
    static_assert(
        std::is_same<List<T>::const_iterator::reference, const T &>::value,
        "const_iterator::reference has unexpected type");
  }

  { // use stdlib functionality
    List<T> list;
    list.push_back(1.0);
    list.push_back(2.0);
    list.push_back(3.0);
    list.push_back(40.0);
    list.push_back(30.0);
    // use std::distance (requires difference type)
    [[maybe_unused]] auto difference = std::distance(list.begin(), list.end());

    TEST_ASSERT(difference == 5,
                "difference obtained from std::distance is wrong");

    // apply an stdlib algorithm relying on bidirectional iterators: reorder all
    // elements > 10 to the front (while keeping relative order)
    [[maybe_unused]] auto it = std::stable_partition(
        list.begin(), list.end(),
        [](const List<T>::value_type &value) { return value > 10.0; });

    TEST_ASSERT(*it == 1.0, "partitioning did not proceed as expected");
  }
  return 0;
}
