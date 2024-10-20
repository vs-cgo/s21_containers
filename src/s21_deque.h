#ifndef S21_DEQUE_H_
#define S21_DEQUE_H_

#include <iostream>

namespace s21 {
template <class T>
class Deque {
 public:
  //  Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  struct Node {
    Node *prev;
    Node *next;
    value_type value;
  };

  // Functions
  Deque();
  Deque(std::initializer_list<value_type> const &items);
  Deque(const Deque &d);
  Deque(Deque &&d);
  Deque &operator=(const Deque &d);
  ~Deque();

  // Element access
  const_reference front();
  const_reference back();
  reference operator[](const size_type index) const;

  // Capacity
  bool empty();
  size_type size() const;

  // Modifiers
  void push_back(const_reference value);
  void push_front(const_reference value);
  void pop_back();
  void pop_front();
  void swap(Deque &other);

 private:
  Node *head_;
  Node *tail_;
  size_type size_;
};

template <typename T>
Deque<T>::Deque() {
  this->head_ = nullptr;
  this->tail_ = nullptr;
  this->size_ = 0;
};

// Functions
template <typename T>
Deque<T>::Deque(std::initializer_list<value_type> const &items) {
  this->size_ = 0;
  for (size_t i = 0; i < items.size(); ++i) {
    Node *ptr = new Node();
    ptr->value = *(items.begin() + i);
    if (this->empty()) {
      tail_ = ptr;
      head_ = tail_;
    } else {
      tail_->next = ptr;
      ptr->prev = tail_;
      tail_ = ptr;
    }
    this->size_ += 1;
  }
};

template <typename T>
Deque<T>::Deque(Deque &&d) : Deque() {
  this->swap(d);
};

template <typename T>
Deque<T> &Deque<T>::operator=(const Deque &d) {
  if (this->size_) this->~Deque();
  Node *t = d.head_;
  while (t) {
    push_back(t->value);
    t = t->next;
  }
  return *this;
};

template <typename T>
Deque<T>::Deque(const Deque &d) : Deque() {
  Node *t = d.head_;
  while (t) {
    this->push_back(t->value);
    t = t->next;
  }
};

template <typename T>
Deque<T>::~Deque() {
  if (!this->empty()) {
    while (head_->next) {
      Node *t = head_;
      head_ = head_->next;
      delete t;
    }
  }
  if (tail_) delete tail_;
  head_ = nullptr;
  tail_ = nullptr;
  size_ = 0;
};

// Element access
template <typename T>
typename Deque<T>::const_reference Deque<T>::front() {
  return head_->value;
};

template <typename T>
typename Deque<T>::const_reference Deque<T>::back() {
  return tail_->value;
};

template <typename T>
typename Deque<T>::reference Deque<T>::operator[](const size_type index) const {
  if (!head_) return nullptr;
  Node *tmp = head_;
  for (size_type i = 0; i < index; i++) {
    tmp = tmp->next;
    if (!tmp) return nullptr;
  }
  return tmp->value;
}

// Capacity
template <typename T>
bool Deque<T>::empty() {
  if (size_) return false;
  return true;
};

template <typename T>
typename Deque<T>::size_type Deque<T>::size() const {
  return size_;
};

// Modifiers
template <typename T>
void Deque<T>::push_back(const_reference value) {
  Node *ptr = new Node();
  ptr->value = value;
  if (this->empty()) {
    tail_ = ptr;
    head_ = tail_;
  } else {
    tail_->next = ptr;
    ptr->prev = tail_;
    tail_ = ptr;
  }
  this->size_ += 1;
};

template <typename T>
void Deque<T>::push_front(const_reference value) {
  Node *ptr = new Node();
  ptr->value = value;
  if (this->empty()) {
    tail_ = ptr;
    head_ = tail_;
  } else {
    ptr->next = head_;
    head_->prev = ptr;
    head_ = ptr;
  }
  this->size_ += 1;
};

template <typename T>
void Deque<T>::pop_back() {
  if (size_) {
    Node *t = this->tail_;
    t = t->prev;
    delete tail_;
    t->next = nullptr;
    tail_ = t;
    size_ -= 1;
  }
};

template <typename T>
void Deque<T>::pop_front() {
  if (size_) {
    Node *t = this->head_;
    t = t->next;
    delete head_;
    head_ = t;
    t->prev = nullptr;
    size_ -= 1;
  }
};

template <typename T>
void Deque<T>::swap(Deque &other) {
  std::swap(this->head_, other.head_);
  std::swap(this->tail_, other.tail_);
  std::swap(this->size_, other.size_);
};

}  // namespace s21

#endif  // S21_DEQUE_H_