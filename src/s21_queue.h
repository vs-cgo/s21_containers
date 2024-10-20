#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_

#include "s21_deque.h"

namespace s21 {
template <class T, class Container = Deque<T>>
class Queue {
 public:
  //  Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // Functions
  Queue();
  Queue(std::initializer_list<value_type> const &items);
  Queue(const Queue &q);
  Queue(Queue &&q);
  Queue &operator=(Queue &&q);
  ~Queue(){};

  // Element access
  const_reference front();
  const_reference back();

  // Capacity
  bool empty();
  size_type size();

  // Modifiers
  void push(const_reference value);
  void pop();
  void swap(Queue &other);
  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  Container d;
};

// Functions
template <typename T, typename Container>
Queue<T, Container>::Queue() : d(){};

template <typename T, typename Container>
Queue<T, Container>::Queue(std::initializer_list<value_type> const &items)
    : d(items){};

template <typename T, typename Container>
Queue<T, Container>::Queue(const Queue &q) : d(q.d){};

template <typename T, typename Container>
Queue<T, Container>::Queue(Queue &&q) : d(std::move(q.d)){};

template <typename T, typename Container>
Queue<T, Container> &Queue<T, Container>::operator=(Queue &&q) {
  this->swap(q);
  q.~Deque();
  return *this;
};

// Element access
template <typename T, typename Container>
typename Queue<T, Container>::const_reference Queue<T, Container>::front() {
  return d.front();
};

template <typename T, typename Container>
typename Queue<T, Container>::const_reference Queue<T, Container>::back() {
  return d.back();
};

// Capacity
template <typename T, typename Container>
bool Queue<T, Container>::empty() {
  return d.empty();
};

template <typename T, typename Container>
typename Queue<T, Container>::size_type Queue<T, Container>::size() {
  return d.size();
};

// Modifiers
template <typename T, typename Container>
void Queue<T, Container>::push(const_reference value) {
  d.push_back(value);
};

template <typename T, typename Container>
void Queue<T, Container>::pop() {
  d.pop_front();
};

template <typename T, typename Container>
void Queue<T, Container>::swap(Queue &other) {
  d.swap(other.d);
};

template <typename T, typename Container>
template <typename... Args>
void Queue<T, Container>::insert_many_back(Args &&...args) {
  for (auto it : {std::forward<Args>(args)...}) {
    push(it);
  }
};

}  // namespace s21

#endif  // 21_QUEUE_H_