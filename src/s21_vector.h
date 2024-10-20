#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

#include <iostream>
#include <limits>

namespace s21 {
using namespace std;
template <class T>
class Vector {
 public:
  // Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // Functions
  Vector();
  explicit Vector(size_type);
  Vector(initializer_list<value_type> const &items);
  Vector(const Vector &v);
  Vector(Vector &&v);
  Vector &operator=(Vector &&v);
  Vector &operator=(const Vector &v);
  ~Vector();

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
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  // Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(Vector &other);
  template <typename... Args>
  void insert_many_back(Args &&...args);
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);

 private:
  value_type *data_;
  size_type size_;
  size_type capacity_;
};

// Functions
template <typename T>
Vector<T>::Vector() {
  size_ = 0;
  capacity_ = 0;
  data_ = nullptr;
};

template <typename T>
Vector<T>::Vector(size_type n) {
  size_ = n;
  capacity_ = n;
  data_ = new value_type[n];
};

template <typename T>
Vector<T>::Vector(initializer_list<value_type> const &items) {
  size_ = items.size();
  capacity_ = items.size();
  data_ = new value_type[size_];
  copy(items.begin(), items.end(), data_);
};

template <typename T>
Vector<T>::Vector(const Vector &v) {
  this->size_ = v.size_;
  this->capacity_ = v.capacity_;
  data_ = new T[v.size_];
  copy(v.data_, v.data_ + v.size_, this->data_);
};

template <typename T>
Vector<T>::Vector(Vector &&v) {
  this->size_ = v.size_;
  this->capacity_ = v.capacity_;
  this->data_ = v.data_;
  v.size_ = 0;
  v.capacity_ = 0;
  v.data_ = 0;
};

template <typename T>
Vector<T> &Vector<T>::operator=(Vector &&v) {
  if (this != &v) {
    if (this->data_) delete[] this->data_;
    this->size_ = v.size_;
    this->capacity_ = v.capacity_;
    this->data_ = v.data_;
  }
  v.size_ = 0;
  v.capacity_ = 0;
  if (v.data_) delete[] v.data_;
  v.data_ = nullptr;
  return *this;
};

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector &v) {
  if (this != &v) {
    if (this->data) delete[] this->data_;
    data_ = new T[v.capacity_];
    std::copy(v.data_, v.data_ + v.size_, this->data_);
    this->size_ = v.size_;
    this->capacity_ = v.capacity_;
  }
  return *this;
};

template <typename T>
Vector<T>::~Vector() {
  size_ = 0;
  capacity_ = 0;
  delete[] data_;
}

// Element access
template <typename T>
typename Vector<T>::reference Vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Invalid index");
  }
  return data_[pos];
};

template <typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type pos) {
  if ((size_ - 1) < pos) {
    throw std::out_of_range("Invalid index");
  }
  return data_[pos];
};

template <typename T>
typename Vector<T>::const_reference Vector<T>::front() {
  return data_[0];
};

template <typename T>
typename Vector<T>::const_reference Vector<T>::back() {
  return data_[size_ - 1];
};

template <typename T>
typename Vector<T>::iterator Vector<T>::data() {
  return data_;
};

template <typename T>
bool Vector<T>::empty() {
  if (size_) return false;
  return true;
};

template <typename T>
typename Vector<T>::size_type Vector<T>::max_size() {
  return (std::numeric_limits<size_type>::max() / sizeof(value_type) / 2);
};

template <typename T>
typename Vector<T>::size_type Vector<T>::size() {
  return size_;
};

template <typename T>
void Vector<T>::reserve(size_type size) {
  if (size <= capacity_) {
    return;
  }
  T *new_data = new T[size];
  if (data_) {
    for (size_t i = 0; i < size_; ++i) {
      new_data[i] = data_[i];
    }
  }
  delete[] this->data_;
  data_ = new_data;
  capacity_ = size;
};

template <typename T>
typename Vector<T>::size_type Vector<T>::capacity() {
  return capacity_;
};

template <typename T>
typename Vector<T>::iterator Vector<T>::begin() {
  return data_;
};

template <typename T>
typename Vector<T>::iterator Vector<T>::end() {
  return data_ + size_;
};

template <typename T>
void Vector<T>::shrink_to_fit() {
  if (size_ == capacity_) {
    return;
  }
  if (!size_) {
    if (data_) delete[] data_;
    capacity_ = 0;
  } else {
    T *new_data = new T[size_];
    for (size_t i = 0; i < size_; i++) {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = size_;
  }
};

template <typename T>
void Vector<T>::clear() {
  size_ = 0;
};

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type index = pos - this->begin();
  if (index > size_) {
    throw std::out_of_range("Invalid index");
  }
  this->push_back(value);
  for (size_t i = size_ - 1; i > index; --i) {
    std::swap(data_[i], data_[i - 1]);
  }
  return data_ + index;
};

template <typename T>
void Vector<T>::push_back(const_reference value) {
  size_type new_capacity = 0;
  if (size_ == capacity_) {
    if (!capacity_)
      new_capacity = 1;
    else
      new_capacity = size_ * 2;
    this->reserve(new_capacity);
  }
  data_[size_] = value;
  ++size_;
};

template <typename T>
void Vector<T>::pop_back() {
  if (size_ > 0) --size_;
};

template <typename T>
void Vector<T>::swap(Vector &other) {
  if (this != &other) {
    std::swap(this->size_, other.size_);
    std::swap(this->capacity_, other.capacity_);
    std::swap(this->data_, other.data_);
  }
};

template <typename T>
void Vector<T>::erase(iterator pos) {
  size_type index = pos - this->begin();
  if (index > size_) {
    throw std::out_of_range("Invalid index");
  }
  for (size_t i = index; i < size_ - 1; i++) {
    data_[i] = data_[i + 1];
  }
  --size_;
};

template <typename T>
template <typename... Args>
void Vector<T>::insert_many_back(Args &&...args) {
  for (auto it : {std::forward<Args>(args)...}) {
    push_back(it);
  }
};

template <typename T>
template <typename... Args>
typename Vector<T>::iterator Vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  iterator it = const_cast<iterator>(pos);
  for (auto value : {std::forward<Args>(args)...}) {
    it = insert(it, value);
    it++;
  }
  return --it;
};

}  // namespace s21

#endif  // S21_VECTOR_H_