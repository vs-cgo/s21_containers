#ifndef _S21_CONTAINERS_S21_LIST_H_
#define _S21_CONTAINERS_S21_LIST_H_

#include <iostream>
#include <limits>
#include <string>

namespace s21 {
template <class T>
struct NodeBase {
  NodeBase *next;
  NodeBase *prev;
};

template <class T>
struct Head : public NodeBase<T> {
  size_t size_;
  Head() {
    this->next = this->prev = this;
    size_ = 0;
  };
  Head(Head &&other) noexcept : size_(other.size_) {
    if (other.next == &other) {
      this->next = this->prev = this;
    } else {
      this->next = other.next;
      this->prev = other.prev;
      this->next->prev = this->prev->next = this;
      other.next = other.prev = &other;
      other.size_ = 0;
    }
  }
};

template <class T>
struct Node : public NodeBase<T> {
  T value;
  Node() : value{0} { this->next = this->prev = nullptr; };
  Node(T v) : value{v} { this->next = this->prev = nullptr; };
};

template <class T>
class list {
  // friend std::ostream & operator<<(std::ostream &, const S21List &);
 public:
  class ListIterator;
  class ListConstIterator;
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;

  list() noexcept;
  explicit list(size_type);
  list(std::initializer_list<value_type> const &items);
  list(const list &);
  list(list &&) noexcept;
  ~list() noexcept;
  list<T> &operator=(list &&l) noexcept;

  // Element access
  const_reference front() const noexcept;
  const_reference back() const noexcept;

  // List Iterators
  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;

  // Capacity
  bool empty() const noexcept;
  inline size_type size() const noexcept;
  inline size_type max_size() const noexcept;

  // Modifiers
  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  template <class... Args>
  iterator insert_many(const_iterator pos, Args... args);
  template <class... Args>
  void insert_many_back(Args &&...args);
  template <class... Args>
  void insert_many_front(Args &&...args);
  void erase(iterator pos) noexcept;
  void push_back(const_reference value);
  void pop_back() noexcept;
  void push_front(const_reference value);
  void pop_front() noexcept;
  void swap(list &other) noexcept;
  template <class Compare = std::less<T>>
  void merge(list &other, Compare cmp = Compare{}) noexcept;
  void splice(const_iterator pos, list &other) noexcept;
  void reverse() noexcept;
  void unique() noexcept;
  template <class Compare = std::less<T>>
  void sort(Compare cmp = Compare{}) noexcept;
  template <class Compare>
  void quick_sort(iterator, iterator, size_type n, Compare);
  void print() const noexcept {
    for (const_iterator start = begin(); start != end(); ++start) {
      std::cout << (start == begin() ? "" : " ") << *start;
    };
    std::cout << '\n';
  };
  class ListIterator {
   public:
    ListIterator() noexcept : ptr_(nullptr){};
    ListIterator(Node<T> *x) noexcept : ptr_(x){};
    ListIterator(const ListIterator &other) : ptr_(other.ptr_){};
    ~ListIterator() noexcept {};
    iterator &operator=(iterator const &other) {
      ptr_ = other.ptr_;
      return *this;
    };
    reference operator*() { return ptr_->value; };

    iterator &operator++() {
      ptr_ = (Node<T> *)ptr_->next;
      return *this;
    }
    iterator operator++(int) {
      iterator tmp(*this);
      ++(*this);
      return tmp;
    }
    iterator &operator--() {
      ptr_ = (Node<T> *)ptr_->prev;
      return *this;
    }
    iterator operator--(int) {
      iterator tmp(*this);
      --(*this);
      return tmp;
    }
    iterator &operator+=(size_type n) {
      while (n-- > 0) ptr_ = (Node<T> *)ptr_->next;
      return *this;
    }
    iterator &operator-=(size_type n) {
      while (n-- > 0) ptr_ = (Node<T> *)ptr_->prev;
      return *this;
    }
    iterator operator+(size_type n) {
      iterator temp = *this;
      while (n-- > 0) ++temp;
      return temp;
    }
    iterator operator-(size_type n) {
      iterator temp = *this;
      while (n-- > 0) --temp;
      return *temp;
    }
    bool operator==(iterator &other) const {
      if (ptr_ == other.ptr_) return true;
      return false;
    }
    bool operator!=(iterator &other) const {
      if (ptr_ != other.ptr_) return true;
      return false;
    }
    iterator &hook(Node<value_type> *temp) {
      temp->prev = ptr_->prev;
      temp->next = ptr_;
      ptr_->prev->next = temp;
      ptr_->prev = temp;
      return --(*this);
    }
    void unhook() {
      ptr_->prev->next = ptr_->next;
      ptr_->next->prev = ptr_->prev;
      delete ptr_;
    }
    Node<value_type> *GetPtr() noexcept { return ptr_; }

   private:
    Node<value_type> *ptr_;
  };

  class ListConstIterator {
   public:
    ListConstIterator() noexcept : ptr_(nullptr){};
    ListConstIterator(const Node<T> *x) noexcept : ptr_(x){};
    ListConstIterator(iterator &x) noexcept
        : ptr_((const Node<T> *)x.GetPtr()){};
    ListConstIterator(iterator &&x) noexcept
        : ptr_((const Node<T> *)x.GetPtr()){};

    ~ListConstIterator() noexcept {};
    const_reference operator*() const { return ptr_->value; };

    const_iterator &operator++() {
      ptr_ = (Node<T> *)ptr_->next;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator tmp(*this);
      ++(*this);
      return tmp;
    }
    const_iterator &operator--() {
      ptr_ = (Node<T> *)ptr_->prev;
      return *this;
    }
    const_iterator operator--(int) {
      const_iterator tmp(*this);
      --(*this);
      return tmp;
    }
    bool operator==(const_iterator const &other) const {
      if (ptr_ == other.ptr_) return true;
      return false;
    }
    bool operator!=(const_iterator const &other) const {
      if (ptr_ != other.ptr_) return true;
      return false;
    }
    const Node<value_type> *GetPtr() const noexcept { return ptr_; }

   private:
    const Node<value_type> *ptr_;
  };

 private:
  Head<value_type> head_;
};

// Construction
// default
template <class T>
list<T>::list() noexcept {}

// parameterized constructor
template <class T>
list<T>::list(size_type n) : list() {
  try {
    for (; n > 0; --n) {
      push_back(T{});
    }
  } catch (...) {
  }
}
// initializer list construction
template <class T>
list<T>::list(std::initializer_list<T> const &items) : list() {
  for (auto i : items) {
    try {
      push_back(i);
    } catch (...) {
    }
  }
}
// copy constructor
template <class T>
list<T>::list(const list &l) : list() {
  for (const_iterator x = l.begin(); x != l.end(); ++x) {
    push_back(*x);
  }
}
// move constructor
template <class T>
list<T>::list(list &&l) noexcept : list() {
  if (l.head_.next == &l.head_) {
    head_.next = head_.prev = &head_;
    head_.size_ = 0;
  } else {
    head_.next = l.head_.next;
    head_.prev = l.head_.prev;
    head_.next->prev = &head_;
    head_.prev->next = &head_;
    head_.size_ = l.head_.size_;
    l.head_.next = &(l.head_);
    l.head_.prev = &(l.head_);
    l.head_.size_ = 0;
  }
}

// Destructor
template <class T>
list<T>::~list() noexcept {
  for (Node<T> *temp = (Node<T> *)head_.next; head_.next != &head_;
       temp = (Node<T> *)head_.next) {
    head_.next = head_.next->next;
    delete temp;
  }
}

// Assignment operator overload for moving object
template <class T>
list<T> &list<T>::operator=(list &&l) noexcept {
  clear();
  if (l.head_.next != &l.head_) {
    head_.next = l.head_.next;
    head_.prev = l.head_.prev;
    head_.next->prev = &head_;
    head_.prev->next = &head_;
    head_.size_ = l.head_.size_;
  }
  l.head_.next = &(l.head_);
  l.head_.prev = &(l.head_);
  l.head_.size_ = 0;
  return *this;
}
// Need assignment copy?
/*
  template <class T>
  list<T> & list<T>::operator=(list &l) {
    return *this;
  }
*/

// Element access
// front
template <typename T>
typename list<T>::const_reference list<T>::front() const noexcept {
  return *begin();  //((Node<T> *)head_.next)->value;
}
// back
template <class T>
typename list<T>::const_reference list<T>::back() const noexcept {
  return *(--end());  //((Node<T> *)head_.prev)->value;
}

// List Iterators
// begin
template <class T>
typename list<T>::iterator list<T>::begin() noexcept {
  return iterator((Node<T> *)head_.next);
}
// end
template <class T>
typename list<T>::iterator list<T>::end() noexcept {
  return iterator((Node<T> *)&head_);
}
// begin const
template <class T>
typename list<T>::const_iterator list<T>::begin() const noexcept {
  return const_iterator((const Node<T> *)head_.next);
}
// end const
template <class T>
typename list<T>::const_iterator list<T>::end() const noexcept {
  return const_iterator((const Node<T> *)&head_);
}
// Capacity
//  empty
template <class T>
bool list<T>::empty() const noexcept {
  if (head_.size_ == 0) return true;
  return false;
}

// size
template <class T>
typename list<T>::size_type list<T>::size() const noexcept {
  return head_.size_;
}

// max_size
template <class T>
typename list<T>::size_type list<T>::max_size() const noexcept {
  return (std::numeric_limits<size_type>::max() / sizeof(Node<T>) / 2);
};

// Modifiers
// clear
template <class T>
void list<T>::clear() noexcept {
  for (Node<T> *temp = (Node<T> *)head_.next; temp != (Node<T> *)&head_;
       temp = (Node<T> *)head_.next) {
    head_.next = head_.next->next;
    delete temp;
  }
  head_.next = head_.prev = &head_;
  head_.size_ = 0;
}

// insert
template <class T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  try {
    Node<T> *temp = new Node<T>{value};
    head_.size_ += 1;
    return pos.hook(temp);
  } catch (...) {
    std::cout << "no memory allocated\n";
    throw;
  }
}
// insert_many
template <class T>
template <class... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args... args) {
  iterator temp = const_cast<Node<T> *>(pos.GetPtr()), res;
  ++temp;
  (temp... = insert(--temp, std::forward<Args>(args)));
  res = --temp;
  return res;
}
// insert_many_back
template <class T>
template <class... Args>
void list<T>::insert_many_back(Args &&...args) {
  for (auto m : {(std::forward<Args>(args))...}) {
    push_back(m);
  }
}

// insert_many_front
template <class T>
template <class... Args>
void list<T>::insert_many_front(Args &&...args) {
  iterator pos = begin();
  for (auto m : {(std::forward<Args>(args))...}) {
    insert(pos, m);
  }
}

// erase
template <class T>
void list<T>::erase(iterator pos) noexcept {
  --(head_.size_);
  pos.unhook();
}

// push_back
template <class T>
void list<T>::push_back(typename list<T>::const_reference value) {
  try {
    Node<T> *temp = new Node<T>{value};
    head_.size_ += 1;
    temp->next = head_.prev->next;
    temp->prev = head_.prev;
    head_.prev->next = temp;
    head_.prev = temp;
  } catch (...) {
    std::cout << "no memmory allocated in push_back\n";
    throw;
  }
}

// pop_back
template <class T>
void list<T>::pop_back() noexcept {
  erase(--end());
}

// push_front
template <class T>
void list<T>::push_front(typename list<T>::const_reference value) {
  insert(begin(), value);
}

// pop_front
template <class T>
void list<T>::pop_front() noexcept {
  erase(begin());
}
// swap
template <class T>
void list<T>::swap(list<T> &other) noexcept {
  list<T> temp(std::move(other));
  other = std::move(*this);
  *this = std::move(temp);
}
// merge
template <class T>
template <class Compare>
void list<T>::merge(list<T> &other, Compare cmp) noexcept {
  if (&other != this) {
    if (head_.next == &head_) {
      swap(other);
    } else if (other.head_.next != &other.head_) {
      Node<T> *r = (Node<T> *)other.head_.next, *temp = r;
      iterator l = begin(), e = end();
      for (; r != (Node<T> *)&other.head_;) {
        if (l == e || cmp(r->value, *l)) {
          temp = r;
          r = (Node<T> *)r->next;
          l.hook(temp);
          ++head_.size_;
        } else {
          ++l;
        }
      }
      other.head_.next = other.head_.prev = &other.head_;
      other.head_.size_ = 0;
    }
  }
}
// splice
template <class T>
void list<T>::splice(const_iterator pos, list &l) noexcept {
  if (l.head_.next != &l.head_) {
    Node<T> *ptr = (Node<T> *)pos.GetPtr(), *start = (Node<T> *)l.head_.next,
            *fin = (Node<T> *)l.head_.prev;
    ptr->prev->next = start;
    start->prev = ptr->prev;
    ptr->prev = fin;
    fin->next = ptr;
    this->head_.size_ += l.head_.size_;
    l.head_.next = l.head_.prev = &l.head_;
  }
  l.head_.size_ = 0;
}

// reverse
template <class T>
void list<T>::reverse() noexcept {
  Node<T> *ptr = (Node<T> *)&head_;
  do {
    std::swap(ptr->next, ptr->prev);
    ptr = (Node<T> *)ptr->next;
  } while (ptr != (Node<T> *)&head_);
}
// unique
template <class T>
void list<T>::unique() noexcept {
  iterator start = begin(), fin = end(), next = ++(begin());
  for (; next != fin; ++next) {
    if (*start == *next) {
      erase(next);
      next = start;
    } else {
      ++start;
    }
  }
}

// sort
template <class T>
template <class Compare>
void list<T>::sort(Compare cmp) noexcept {
  if (head_.next != &head_ && head_.size_ > 1) {
    quick_sort(begin(), --(end()), head_.size_, cmp);
  }
}
template <class T>
template <class Compare>
void list<T>::quick_sort(iterator left, iterator right, size_type n,
                         Compare cmp) {
  size_type m = n / 2, l = 1, r = n;
  iterator mid = left + m, start = left, fin = right;
  while (l <= r) {
    while (cmp(*start, *mid)) {
      ++start;
      ++l;
    }
    while (cmp(*mid, *fin)) {
      --fin;
      --r;
    }
    if (l <= r) {
      Node<value_type> *l_node = start.GetPtr(), *r_node = fin.GetPtr();
      if (l_node != r_node) {
        if (l_node->next == r_node) {
          l_node->next = r_node->next;
          l_node->next->prev = l_node;
          l_node->prev->next = r_node;
          r_node->prev = l_node->prev;
          r_node->next = l_node;
          l_node->prev = r_node;
        } else {
          std::swap(l_node->next, r_node->next);
          std::swap(l_node->prev, r_node->prev);
          l_node->next->prev = l_node->prev->next = l_node;
          r_node->next->prev = r_node->prev->next = r_node;
        }
        iterator temp = start;
        start = fin;
        fin = temp;
        if (l == 1) left = start;
        if (r == n) right = fin;
      }
      ++start, --fin;
      ++l, --r;
    }
  }
  if (r > 1) quick_sort(left, fin, r, cmp);
  if (n > l) quick_sort(start, right, n - l + 1, cmp);
}

}  // end namespace s21
#endif  //_S21_CONTAINERS_S21_LIST_H_
