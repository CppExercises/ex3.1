#pragma once
#include <cstddef>
#include <iostream>
#include <iterator>
#include <list>
#include <utility>
#include <memory>

template <class T, std::enable_if_t<std::is_default_constructible<T>::value,
                                    bool> = true>
class List { 
public:
  using size_type = std::size_t;
  using value_type = T;

private:
  struct Node { 
    Node *prev = this;
    Node *next = this;
    T value;

  };

  // data members
  Node sentinel;
  Node *root = &sentinel;
  size_type size = 0;

  // helper functions
  void swap(List &&other) {
    std::swap(root, other.root);
    std::swap(size, other.size);
  }

  static void erase(Node *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    // downcast required when deleting
    delete node;
  }
  void append(const List &other) {
    for (const auto &item : other) {
      push_back(item);
    }
  }
  void clear() {
    auto node = root->next;
    while (node != root) {
      const auto next = node->next;
      erase(node);
      node = next;
    }
  }

public:
  void push_back(const value_type &value) {
    const auto new_node = new Node{root->prev, root, value};
    root->prev->next = new_node;
    root->prev = new_node;
    ++size;
  }

  void push_front(const value_type &value) {
    const auto new_node = new Node{root, root->next, value};
    root->next->prev = new_node;
    root->next = new_node;
    ++size;
  }

  List() = default; // default construct 'empty' list with sentinel

  List(List &&other) { // move ctor
    swap(*this, other);
  }

  List &operator=(List &&other) { // move assign
    swap(*this, other);
    return *this;
  }

  List(const List &other) { // copy ctor
    append(other);
  }

  List &operator=(const List &other) { // copy assign
    clear();
    append();
    return *this;
  }

  ~List() { // dtor
    clear();
  }

  // ------------ SOLUTION START
  
  
  struct iterator
  {
    Node *node;
    using value_type = T;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;

    using pointer = T*;
    using reference = T&;
    
    iterator(Node* node)
    {
       this->node = node;
    }

    T& operator*()
    {
      return node->value;
    }

    iterator operator++()
    {
      this->node = this->node->next;
      return *this;
    }

    iterator operator--()
    {
      this->node = this->node->prev;
      return *this;
    }

    bool operator==(iterator it)
    {
      return this->node->value == it.node->value;
    }

    bool operator!=(iterator it)
    {
      return this->node->value != it.node->value;
    }

    T* operator->()
    {
      return &node->value;
    }

  };


  struct const_iterator
  {
    Node *node;
    using value_type = const T;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;

    using pointer = const T*;
    using reference = const T&;
    
    const_iterator(Node* node)
    {
       this->node = node;
    }

    T& operator*()
    {
      return node->value;
    }

    const_iterator operator++()
    {
      this->node = this->node->next;
      return *this;
    }

    const_iterator operator--()
    {
      this->node = this->node->prev;
      return *this;
    }

    bool operator==(const_iterator it)
    {
      return this->node->value == it.node->value;
    }

    bool operator!=(const_iterator it)
    {
      return this->node->value != it.node->value;
    }

    T* operator->()
    {
      return &node->value;
    }

  };


  iterator begin()
  {
    return iterator{this->root->next};
  }

  iterator end()
  {
    return iterator{this->root};
  }

  const_iterator begin() const
  {
    return const_iterator{this->root->next};
  }

  const_iterator end() const
  {
    return const_iterator{this->root};
  }

  const_iterator cbegin() const
  {
    return const_iterator{this->root->next};
  }

  const_iterator cend() const
  {
    return const_iterator{this->root};
  }


  // ------------ SOLUTION END
};
