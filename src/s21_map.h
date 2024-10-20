#ifndef _S21_CONTAINERS_S21_MAP_H_
#define _S21_CONTAINERS_S21_MAP_H_

#include <vector>

#include "s21_rbtree.h"

namespace s21 {
template <class Key, class T, class Compare = std::less<Key>>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const reference;
  using container = RBTree<key_type, mapped_type, Compare>;
  using iterator = typename container::iterator;
  using const_iterator = typename container::const_iterator;
  using size_type = size_t;

  // Member functions
  map();
  map(std::initializer_list<value_type> const& items);
  map(const map& m);
  map(map&& m);
  ~map();
  map& operator=(const map& m);
  map& operator=(map&& m);

  // Element access
  T& at(const Key& key);
  T& operator[](const Key& key);

  // Iterators
  iterator begin();
  iterator end();

  // Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // Modifiers
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  // For part3
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args... args);
  void erase(iterator pos);
  void swap(map& other);
  void merge(map& other);

  // Lookup
  bool contains(const Key& key);

  void print() { t.print(); };

 private:
  container t;
};
// Member functions
// Ctor default
template <class K, class T, class Compare>
map<K, T, Compare>::map() : t() {}

// Ctor initializer_list
template <class K, class T, class Compare>
map<K, T, Compare>::map(std::initializer_list<value_type> const& items)
    : t(items){};

// Ctor copy
template <class K, class T, class Compare>
map<K, T, Compare>::map(const map& rhs) : t(rhs.t){};

// Ctor move
template <class K, class T, class Compare>
map<K, T, Compare>::map(map&& rhs) : t(std::move(rhs.t)){};

// Dtor
template <class K, class T, class Compare>
map<K, T, Compare>::~map(){};

// Assignment copy
template <class K, class T, class Compare>
map<K, T, Compare>& map<K, T, Compare>::operator=(const map& rhs) {
  t = rhs.t;
  return *this;
};

// Assignment move
template <class K, class T, class Compare>
map<K, T, Compare>& map<K, T, Compare>::operator=(map&& rhs) {
  t = std::move(rhs.t);
  return *this;
};

// Element access
// At
template <class K, class T, class Compare>
typename map<K, T, Compare>::mapped_type& map<K, T, Compare>::at(const K& key) {
  return t.at(key);
}
// Operator[]
template <class K, class T, class Compare>
typename map<K, T, Compare>::mapped_type& map<K, T, Compare>::operator[](
    const K& key) {
  return t[key];
}

// Iterators
// Begin
template <class K, class T, class Compare>
typename map<K, T, Compare>::iterator map<K, T, Compare>::begin() {
  return t.begin();
}
// End
template <class K, class T, class Compare>
typename map<K, T, Compare>::iterator map<K, T, Compare>::end() {
  return t.end();
}

// Capacity
template <class K, class T, class Compare>
bool map<K, T, Compare>::empty() {
  return t.empty();
}
template <class K, class T, class Compare>
typename map<K, T, Compare>::size_type map<K, T, Compare>::size() {
  return t.size();
}
template <class K, class T, class Compare>
typename map<K, T, Compare>::size_type map<K, T, Compare>::max_size() {
  return t.max_size();
}

// Modifiers
// Clear
template <class K, class T, class Compare>
void map<K, T, Compare>::clear() {
  t.clear();
};

// Insert pair
template <class K, class T, class Compare>
std::pair<typename map<K, T, Compare>::iterator, bool>
map<K, T, Compare>::insert(const value_type& value) {
  return t.insert(value);
};

// Insert key and value
template <class K, class T, class Compare>
std::pair<typename map<K, T, Compare>::iterator, bool>
map<K, T, Compare>::insert(const K& key, const T& value) {
  return t.insert(key, value);
}

// Insert_or_assign
template <class K, class T, class Compare>
std::pair<typename map<K, T, Compare>::iterator, bool>
map<K, T, Compare>::insert_or_assign(const K& key, const T& value) {
  return t.insert_or_assign(key, value);
}

// Insert_many (for part 3)
template <class K, class T, class Compare>
template <class... Args>
std::vector<std::pair<typename map<K, T, Compare>::iterator, bool>>
map<K, T, Compare>::insert_many(Args... args) {
  std::vector<std::pair<typename map<K, T, Compare>::iterator, bool>> res = {
      (insert(std::forward<Args>(args)))...};
  return res;
}

// Erase
template <class K, class T, class Compare>
void map<K, T, Compare>::erase(typename map<K, T, Compare>::iterator pos) {
  t.erase(pos);
}

// Swap
template <class K, class T, class Compare>
void map<K, T, Compare>::swap(map<K, T, Compare>& rhs) {
  t.swap(rhs.t);
};

// Merge
template <class K, class T, class Compare>
void map<K, T, Compare>::merge(map<K, T, Compare>& rhs) {
  t.merge(rhs.t);
};

// Lookup
template <class K, class T, class Compare>
bool map<K, T, Compare>::contains(const K& key) {
  return t.contains(key);
};
}  // namespace s21

#endif  // _S21_CONTAINERS_S21_MAP_H_
