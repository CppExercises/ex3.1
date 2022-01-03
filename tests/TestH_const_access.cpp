// This test checks whether the obtained iterators provide const access only
// when expected

#include "testasserts.hpp"
#include <List.hpp>
#include <iostream>
#include <string>
#include <type_traits>

int main() {
  using T = double;

  { // check if nested types for const and non-const iterators exist and if
    // nested value_type reflect constness correctly via the value_type
    using non_const_itertype = List<T>::iterator;
    using const_itertype = List<T>::const_iterator;
    List<T> list;
    [[maybe_unused]] non_const_itertype it = list.begin();
    [[maybe_unused]] const_itertype cit = std::as_const(list).begin();

    static_assert(!std::is_const<List<T>::iterator::value_type>::value,
                  "access is const for non-const iterator");
    static_assert(std::is_const<List<T>::const_iterator::value_type>::value,
                  "access is non-const for const iterator");
  }

  { // check if cbegin and cend return iterators providing const access
    static_assert(
        std::is_same<decltype(List<T>{}.cbegin())::value_type, const T>::value,
        "cbegin() does not return iterator with const access");
    static_assert(
        std::is_same<decltype(List<T>{}.cend())::value_type, const T>::value,
        "cend() does not return iterator with const access");
  }

  { // check if begin and end return iterators providing non-const access
    static_assert(
        std::is_same<decltype(List<T>{}.begin())::value_type, T>::value,
        "begin() does not return iterator with non-const access");
    static_assert(std::is_same<decltype(List<T>{}.end())::value_type, T>::value,
                  "end() does not return iterator with const access");
  }

  { // check if begin and end obtained from a const list result in iterators
    // with const access
    List<T> list;
    list.push_back(1.0);
    [[maybe_unused]] const List<T> &clist = list;
 
    static_assert(
        !std::is_same<decltype(clist.begin())::value_type, T>::value,
        "begin() does not return iterator with const access when obtained from a const list");
    static_assert(
        !std::is_same<decltype(clist.end())::value_type, T>::value,
        "end() does not return iterator with const access when obtained from a const list");
  }

  return 0;
}
