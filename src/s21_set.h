#ifndef S21_SET_H_
#define S21_SET_H_

#include <vector>

#include "s21_avltree.h"

namespace s21 {
template <class Key, class Container = BinaryTree<Key, std::less<Key>>>
class Set {
 public:
  //  Member type
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename Container::Iterator;
  using const_iterator = typename Container::Const_iterator;
  using size_type = size_t;

  // Member functions
  Set();
  Set(std::initializer_list<value_type> const &items);
  Set(const Set &s);
  Set(Set &&s);
  ~Set();
  Set &operator=(Set &&s);

  // Iterators
  iterator begin();
  iterator end();

  // Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // Modifiers
  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(Set &other);
  void merge(Set &other);
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

  // Lookup
  iterator find(const key_type &key);
  bool contains(const key_type &key);

  // Other
  void print() { b.print(); };

 private:
  Container b;
};

// Member functions
template <typename K, typename Container>
Set<K, Container>::Set() : b(){};

template <typename K, typename Container>
Set<K, Container>::Set(std::initializer_list<value_type> const &items)
    : b(items){};

template <typename K, typename Container>
Set<K, Container>::Set(const Set &s) : b(s.b){};

template <typename K, typename Container>
Set<K, Container>::Set(Set &&s) : b(std::move(s.b)){};

template <typename K, typename Container>
Set<K, Container>::~Set(){};

template <typename K, typename Container>
Set<K, Container> &Set<K, Container>::operator=(Set &&s) {
  b = std::move(s.b);
  return *this;
};

// Iterators
template <typename K, typename Container>
typename Set<K, Container>::iterator Set<K, Container>::begin() {
  return b.begin();
};

template <typename K, typename Container>
typename Set<K, Container>::iterator Set<K, Container>::end() {
  return b.end();
};

// Capacity
template <typename K, typename Container>
bool Set<K, Container>::empty() {
  return b.empty();
};

template <typename K, typename Container>
typename Set<K, Container>::size_type Set<K, Container>::size() {
  return b.size();
};

template <typename K, typename Container>
typename Set<K, Container>::size_type Set<K, Container>::max_size() {
  return b.max_size();
};

// Modifiers
template <typename K, typename Container>
void Set<K, Container>::clear() {
  b.clear();
};

template <typename K, typename Container>
std::pair<typename Set<K, Container>::iterator, bool> Set<K, Container>::insert(
    const value_type &value) {
  return b.insert(value);
};

template <typename K, typename Container>
void Set<K, Container>::erase(iterator pos) {
  b.erase(pos);
};

template <typename K, typename Container>
void Set<K, Container>::swap(Set &other) {
  b.swap(other.b);
};

template <typename K, typename Container>
void Set<K, Container>::merge(Set &other) {
  b.merge(other.b);
};

template <typename K, typename Container>
template <typename... Args>
std::vector<std::pair<typename Set<K, Container>::iterator, bool>>
Set<K, Container>::insert_many(Args &&...args) {
  std::vector<std::pair<iterator, bool>> res = {
      (insert(std::forward<Args>(args)))...};
  return res;
}

// Lookup
template <typename K, typename Container>
typename Set<K, Container>::iterator Set<K, Container>::find(
    const key_type &key) {
  return b.find(key);
};

template <typename K, typename Container>
bool Set<K, Container>::contains(const key_type &key) {
  return b.contains(key);
};

}  // namespace s21

#endif  // S21_SET_H