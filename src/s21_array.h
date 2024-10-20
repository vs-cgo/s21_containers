#ifndef S21_ARRAY_H_
#define S21_ARRAY_H_

#include <iostream>

namespace s21 {
template <class T, size_t N>
class Array {
 public:
  //  Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // Functions
  Array();
  Array(std::initializer_list<value_type> const &items);
  Array(const Array &a);
  Array(Array &&a);
  ~Array();
  Array &operator=(Array &&a);
  Array &operator=(const Array &a);

  // Element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  // Iterators
  iterator begin();
  iterator end();

  // Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // Modifiers
  void swap(Array &other);
  void fill(const_reference value);

  // Other
  void print_arr() {
    for (size_type i = 0; i < this->s; ++i) {
      std::cout << arr[i] << ' ';
    }
  }

 private:
  iterator arr;
  size_type s;
};

// Functions
template <typename T, size_t N>
Array<T, N>::Array() : s(N) {
  if (!s)
    arr = nullptr;
  else
    arr = new value_type[s];
};

template <typename T, size_t N>
Array<T, N>::Array(std::initializer_list<value_type> const &items) : Array() {
  if (items.size() > s) {
    throw std::bad_alloc();
  } else {
    size_type i = 0;
    for (auto it = items.begin(); it < items.end(); ++it, ++i) arr[i] = *it;
  }
};

template <typename T, size_t N>
Array<T, N>::Array(const Array &a) : Array() {
  if (a.s > this->s) {
    throw std::out_of_range("Error!");
  } else {
    for (size_type i = 0; i < a.s; ++i) {
      this->arr[i] = a.arr[i];
    }
  }
};

template <typename T, size_t N>
Array<T, N>::Array(Array &&a) : Array() {
  if (a.s > this->s) {
    throw std::out_of_range("Error!!!");
  } else {
    for (size_type i = 0; i < a.s; ++i) {
      std::swap(this->arr[i], a.arr[i]);
    }
    a.s = 0;
  }
};

template <typename T, size_t N>
Array<T, N>::~Array() {
  if (arr) delete[] arr;
  s = 0;
  arr = nullptr;
};

template <typename T, size_t N>
Array<T, N> &Array<T, N>::operator=(Array &&a) {
  if (this != &a) {
    if (arr) delete[] arr;
    arr = nullptr;
    arr = new value_type[a.s];
    for (size_type i = 0; i < s; ++i) {
      arr[i] = std::move(a[i]);
    }
  }
  return *this;
};

template <typename T, size_t N>
Array<T, N> &Array<T, N>::operator=(const Array &a) {
  if (this != &a) {
    if (arr) delete[] arr;
    arr = nullptr;
    arr = new value_type[a.s];
    s = a.s;
    for (size_t i = 0; i < a.s; ++i) {
      arr[i] = a.arr[i];
    }
  }
  return *this;
};

// Element access
template <typename T, size_t N>
typename Array<T, N>::reference Array<T, N>::at(size_type pos) {
  if (pos >= this->s) throw std::out_of_range("Error!!!");
  return arr[pos];
};

template <typename T, size_t N>
typename Array<T, N>::reference Array<T, N>::operator[](size_type pos) {
  return at(pos);
};

template <typename T, size_t N>
typename Array<T, N>::const_reference Array<T, N>::front() {
  return *arr;
};

template <typename T, size_t N>
typename Array<T, N>::const_reference Array<T, N>::back() {
  return *(arr + s - 1);
};

template <typename T, size_t N>
typename Array<T, N>::iterator Array<T, N>::data() {
  return arr;
};

// Iterators
template <typename T, size_t N>
typename Array<T, N>::iterator Array<T, N>::begin() {
  return arr;
};

template <typename T, size_t N>
typename Array<T, N>::iterator Array<T, N>::end() {
  return arr + s;
};

// Capacity
template <typename T, size_t N>
bool Array<T, N>::empty() {
  return !s;
};

template <typename T, size_t N>
typename Array<T, N>::size_type Array<T, N>::size() {
  return s;
};

template <typename T, size_t N>
typename Array<T, N>::size_type Array<T, N>::max_size() {
  return s;
};

// Modifiers
template <typename T, size_t N>
void Array<T, N>::swap(Array &other) {
  if (other.s != this->s)
    throw std::out_of_range("Error!!!");
  else {
    std::swap(other.arr, this->arr);
  }
};

template <typename T, size_t N>
void Array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < s; ++i) arr[i] = value;
};

}  // namespace s21

#endif  // S21_ARRAY_H_