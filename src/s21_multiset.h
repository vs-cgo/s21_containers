#ifndef S21_MULTISET_H_
#define S21_MULTISET_H_

#include <iostream>

#include "s21_avltree.h"

namespace s21 {
template <class Key, class Container = BinaryTree<Key, std::less<Key>>>
class Multiset {
 public:
  // Member type
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename Container::Iterator;
  using const_iterator = typename Container::Const_iterator;
  using size_type = size_t;
  // Member functions
  Multiset();
  Multiset(std::initializer_list<value_type> const &items);
  Multiset(const Multiset &ms);
  Multiset(Multiset &&ms);
  Multiset &operator=(Multiset &&ms);
  ~Multiset();
  // Iterators
  iterator begin();
  iterator end();
  // Capacity
  bool empty();
  size_type size();
  size_type max_size();
  // Modifiers
  void clear();
  iterator insert(const value_type &value);
  void erase(iterator pos);
  void swap(Multiset &other);
  void merge(Multiset &other);
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
  // Lookup
  size_type count(const Key &key);
  iterator find(const Key &key);
  bool contains(const Key &key);
  iterator lower_bound(const key_type &key);
  iterator upper_bound(const key_type &key);
  std::pair<iterator, iterator> equal_range(const key_type &key);
  // Other
  void print() { b.print(); };

 private:
  Container b;
};

template <typename K, typename Container>
Multiset<K, Container>::Multiset() : b(){};

template <typename K, typename Container>
Multiset<K, Container>::Multiset(
    std::initializer_list<value_type> const &items) {
  for (auto i = items.begin(); i != items.end(); ++i) b.insert_for_multiset(*i);
};

template <typename K, typename Container>
Multiset<K, Container>::Multiset(const Multiset &ms) : b(ms.b){};

template <typename K, typename Container>
Multiset<K, Container>::Multiset(Multiset &&ms) : b(std::move(ms.b)){};

template <typename K, typename Container>
Multiset<K, Container> &Multiset<K, Container>::operator=(Multiset &&ms) {
  b = std::move(ms.b);
  return *this;
};

template <typename K, typename Container>
Multiset<K, Container>::~Multiset(){};

template <typename K, typename Container>
typename Multiset<K, Container>::iterator Multiset<K, Container>::begin() {
  return b.begin();
}

template <typename K, typename Container>
typename Multiset<K, Container>::iterator Multiset<K, Container>::end() {
  return b.end();
};

template <typename K, typename Container>
bool Multiset<K, Container>::empty() {
  return b.empty();
};

template <typename K, typename Container>
typename Multiset<K, Container>::size_type Multiset<K, Container>::size() {
  return b.size();
};

template <typename K, typename Container>
typename Multiset<K, Container>::size_type Multiset<K, Container>::max_size() {
  return b.max_size();
};

template <typename K, typename Container>
void Multiset<K, Container>::erase(iterator pos) {
  b.erase(pos);
};

template <typename K, typename Container>
void Multiset<K, Container>::clear() {
  b.clear();
};

template <typename K, typename Container>
typename Multiset<K, Container>::size_type Multiset<K, Container>::count(
    const key_type &key) {
  return b.count(key);
};

template <typename K, typename Container>
typename Multiset<K, Container>::iterator Multiset<K, Container>::find(
    const key_type &key) {
  return b.find(key);
};

template <typename K, typename Container>
bool Multiset<K, Container>::contains(const key_type &key) {
  return b.contains(key);
};

template <typename K, typename Container>
typename Multiset<K, Container>::iterator Multiset<K, Container>::lower_bound(
    const key_type &key) {
  return b.lower_bound(key);
};

template <typename K, typename Container>
typename Multiset<K, Container>::iterator Multiset<K, Container>::upper_bound(
    const key_type &key) {
  return b.upper_bound(key);
};

template <typename K, typename Container>
std::pair<typename Multiset<K, Container>::iterator,
          typename Multiset<K, Container>::iterator>
Multiset<K, Container>::equal_range(const key_type &key) {
  return b.equal_range(key);
}

template <typename K, typename Container>
void Multiset<K, Container>::swap(Multiset &other) {
  b.swap(other.b);
};

template <typename K, typename Container>
void Multiset<K, Container>::merge(Multiset &other) {
  b.merge_for_multiset(other.b);
};

template <typename K, typename Container>
typename Multiset<K, Container>::iterator Multiset<K, Container>::insert(
    const value_type &value) {
  return b.insert_for_multiset(value);
};

template <typename K, typename Container>
template <typename... Args>
std::vector<std::pair<typename Multiset<K, Container>::iterator, bool>>
Multiset<K, Container>::insert_many(Args &&...args) {
  std::vector<std::pair<iterator, bool>> res = {
      (b.insert_many_for_multiset(std::forward<Args>(args)))...};
  return res;
}

}  // namespace s21

#endif  // S21_MULTISET_H_