#ifndef S21_STACK_H_
#define S21_STACK_H_

#include "s21_deque.h"

namespace s21 {
template <class T, class Container = Deque<T>>
class Stack {
 public:
  //  Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // Functions
  Stack();
  Stack(std::initializer_list<value_type> const &items);
  Stack(const Stack &s);
  Stack(Stack &&s);
  Stack &operator=(Stack &&s);
  Stack &operator=(const Stack &s);
  ~Stack(){};

  // Element access
  const_reference top();

  // Capacity
  bool empty();
  size_type size();

  // Modifiers
  void push(const_reference value);
  void pop();
  void swap(Stack &other);
  template <typename... Args>
  void insert_many_front(Args &&...args);

 private:
  Container stack;
};

// Functions
template <typename T, typename Container>
Stack<T, Container>::Stack() : stack(){};

template <typename T, typename Container>
Stack<T, Container>::Stack(std::initializer_list<value_type> const &items)
    : stack(items){};

template <typename T, typename Container>
Stack<T, Container>::Stack(const Stack &s) : stack(s.stack){};

template <typename T, typename Container>
Stack<T, Container>::Stack(Stack &&s) : stack(std::move(s.stack)){};

template <typename T, typename Container>
Stack<T, Container> &Stack<T, Container>::operator=(Stack &&s) {
  stack = std::move(s.stack);
  return *this;
};

template <typename T, typename Container>
Stack<T, Container> &Stack<T, Container>::operator=(const Stack &s) {
  stack = (s.stack);
  return *this;
};

// Element access
template <typename T, typename Container>
typename Stack<T, Container>::const_reference Stack<T, Container>::top() {
  return stack.back();
};

// Capacity
template <typename T, typename Container>
bool Stack<T, Container>::empty() {
  return stack.empty();
};

template <typename T, typename Container>
typename Stack<T, Container>::size_type Stack<T, Container>::size() {
  return stack.size();
};

// Modifiers
template <typename T, typename Container>
void Stack<T, Container>::push(const_reference value) {
  stack.push_back(value);
};

template <typename T, typename Container>
void Stack<T, Container>::pop() {
  stack.pop_back();
};

template <typename T, typename Container>
void Stack<T, Container>::swap(Stack &other) {
  stack.swap(other.stack);
};

template <typename T, typename Container>
template <typename... Args>
void Stack<T, Container>::insert_many_front(Args &&...args) {
  for (auto it : {std::forward<Args>(args)...}) {
    stack.push_front(it);
  }
}
}  // namespace s21

#endif  // S21_STACK_H_