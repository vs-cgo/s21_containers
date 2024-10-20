#ifndef _S21_CONTAINERS_S21_RBTREE_H_
#define _S21_CONTAINERS_S21_RBTREE_H_

#include <iostream>
#include <utility>

namespace s21 {
enum NodeColor { kRed = 0, kBlack };

template <class T>
struct greater {
  constexpr bool operator()(const T &lhs, const T &rhs) const {
    return lhs > rhs;
  }
};
template <class T>
struct less {
  constexpr bool operator()(const T &lhs, const T &rhs) const {
    return lhs < rhs;
  }
};

struct TreeNodeBase {
  s21::NodeColor color;
  TreeNodeBase *parent, *left, *right;
  TreeNodeBase()
      : color(kRed), parent(nullptr), left(nullptr), right(nullptr){};
};
struct TreeNodeHeader {
  TreeNodeBase header;
  size_t count;
  TreeNodeHeader() : header(), count(0){};
  TreeNodeHeader(TreeNodeHeader &&other) : TreeNodeHeader() {
    std::swap(header, other.header);
    std::swap(count, other.count);
  };
  void operator=(TreeNodeHeader &&other) {
    std::swap(header.color, other.header.color);
    std::swap(header.parent, other.header.parent);
    std::swap(header.left, other.header.left);
    std::swap(header.right, other.header.right);
    std::swap(count, other.count);
  }
  void Init(TreeNodeBase *x) { header.left = header.right = x; };
};

template <class Key, class T, class Compare = std::less<Key>>
class RBTree {
 public:
  class RBTreeIterator;
  class RBTreeConstIterator;

  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using iterator = RBTreeIterator;
  using const_iterator = RBTreeConstIterator;
  using size_type = size_t;

  struct TreeNode : public TreeNodeBase {
    key_type key;
    mapped_type value;
    TreeNode() : TreeNodeBase(), key(key_type{}), value(mapped_type{}){};
    explicit TreeNode(key_type k, mapped_type m)
        : TreeNodeBase(), key(k), value(m){};
    TreeNode(TreeNode &other)
        : TreeNodeBase(other), key(other.key), value(other.value){};
  };
  // Member functions
  RBTree() noexcept;
  RBTree(std::initializer_list<value_type> const &items);
  RBTree(const RBTree &other);
  RBTree(RBTree &&other) noexcept;
  ~RBTree();

  RBTree &operator=(const RBTree &other);
  RBTree &operator=(RBTree &&other);

  // Element access
  mapped_type &at(const key_type &);
  mapped_type &operator[](const key_type &);

  // Iterators
  iterator begin();
  iterator end();

  // Capasity
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Modifiers
  void clear() noexcept;
  std::pair<iterator, bool> insert(const value_type &value,
                                   Compare cmp = Compare{});
  std::pair<iterator, bool> insert(const key_type &key,
                                   const mapped_type &value,
                                   Compare cmp = Compare{});
  std::pair<iterator, bool> insert_or_assign(const key_type &,
                                             const mapped_type &,
                                             Compare cmp = Compare{});
  void erase(iterator pos);
  void swap(RBTree &other) noexcept;
  void merge(RBTree &other);
  void getNode(TreeNode *node, RBTree &other);

  inline bool isBlack(TreeNodeBase *node) const noexcept;
  inline void print() const noexcept;

  // Lookup
  bool contains(const key_type &key, Compare cmp = Compare{});

  // Temp
  key_type get() const { return (root_) ? root_->key : key_type{}; };

  // Iterator
  class RBTreeIterator {
   public:
    using node = RBTree<key_type, mapped_type, Compare>::TreeNode;

    RBTreeIterator() noexcept : ptr_(nullptr){};
    RBTreeIterator(node *x) noexcept : ptr_(x){};
    RBTreeIterator(const iterator &other) : ptr_(other.ptr_){};
    RBTreeIterator(iterator &&other) : iterator() {
      std::swap(ptr_, other.ptr_);
    };
    ~RBTreeIterator() { ptr_ = nullptr; };
    RBTreeIterator &operator=(iterator const &other) {
      ptr_ = other.ptr_;
      return *this;
    }
    std::pair<key_type, mapped_type> *operator->() {
      return ((std::pair<key_type, mapped_type> *)&(ptr_->key));
    }
    std::pair<key_type, mapped_type> operator*() {
      return (std::make_pair(ptr_->key, ptr_->value));
    }
    RBTreeIterator &operator++() {
      operInc();
      return *this;
    }
    RBTreeIterator operator++(int) {
      RBTreeIterator temp(*this);
      operInc();
      return temp;
    }
    RBTreeIterator &operator--() {
      operDec();
      return *this;
    }
    RBTreeIterator operator--(int) {
      RBTreeIterator temp(*this);
      operDec();
      return temp;
    }
    bool operator==(const iterator &other) { return ptr_ == other.ptr_; }
    bool operator!=(const iterator &other) { return ptr_ != other.ptr_; }
    TreeNode *getPtr() { return ptr_; }

   protected:
    // Maximum
    void Maximum() {
      for (; ptr_ != nullptr && ptr_->right != nullptr;
           ptr_ = (TreeNode *)ptr_->right) {
      }
    };
    // Increment
    void operInc() {
      if (ptr_ != nullptr) {
        if (ptr_->parent == nullptr) {
          Maximum();
        } else if (ptr_->right != nullptr) {
          ptr_ = static_cast<TreeNode *>(ptr_->right);
          for (; ptr_->left != nullptr;
               ptr_ = static_cast<TreeNode *>(ptr_->left)) {
          }
        } else if (ptr_ == ptr_->parent->left) {
          ptr_ = static_cast<TreeNode *>(ptr_->parent);
        } else if (ptr_ != static_cast<TreeNode *>(ptr_->parent->left)) {
          node *temp = ptr_;
          for (; temp->parent != nullptr &&
                 temp != static_cast<TreeNode *>(temp->parent->left);) {
            temp = static_cast<TreeNode *>(temp->parent);
          }
          if (temp->parent != nullptr)
            ptr_ = static_cast<TreeNode *>(temp->parent);
        }
      }
    }
    // Decrement
    void operDec() {
      if (ptr_ != nullptr) {
        if (ptr_->parent == nullptr) {
          Maximum();
        } else if (ptr_->left != nullptr) {
          ptr_ = static_cast<TreeNode *>(ptr_->left);
          for (; ptr_->right != nullptr;
               ptr_ = static_cast<TreeNode *>(ptr_->right))
            ;
        } else if (ptr_ == ptr_->parent->right) {
          ptr_ = static_cast<TreeNode *>(ptr_->parent);
        } else if (ptr_ != static_cast<TreeNode *>(ptr_->parent->right)) {
          TreeNodeBase *temp = ptr_;
          for (; temp->parent != nullptr && temp != temp->parent->right;) {
            temp = temp->parent;
          }
          ptr_ = static_cast<TreeNode *>(temp->parent);
        }
      }
    }
    // Node
    node *ptr_;
  };
  // ConstIterator
  class RBTreeConstIterator : public RBTreeIterator {
   public:
    using node = RBTree<key_type, mapped_type, Compare>::TreeNode;
    RBTreeConstIterator() noexcept : ptr_(nullptr){};
    explicit RBTreeConstIterator(const node *x) : ptr_(x){};
    RBTreeConstIterator(RBTreeConstIterator &other) noexcept
        : ptr_(other.ptr_){};
    RBTreeConstIterator(RBTreeConstIterator &&other) : RBTreeConstIterator() {
      std::swap(ptr_, other.ptr_);
    };
    ~RBTreeConstIterator() { ptr_ = nullptr; };
    RBTreeConstIterator &operator=(RBTreeConstIterator &rhs) {
      ptr_ = rhs.ptr_;
      return *this;
    };
    RBTreeConstIterator &operator=(RBTreeConstIterator &&rhs) {
      std::swap(ptr_, rhs.ptr_);
      return *this;
    };
    bool operator==(const_iterator &other) { return ptr_ == other.ptr_; }
    bool operator!=(const_iterator &other) { return ptr_ != other.ptr_; }
    TreeNode *getPtr() { return ptr_; }

   protected:
    const node *ptr_;
  };

 protected:
  // Work`s function
  TreeNode *insertW(key_type, mapped_type, Compare cmp = Compare{});
  void insert(TreeNode *node, RBTree &other, Compare cmp = Compare{});
  void recolor(TreeNode *);
  void recolor2(TreeNode *node);
  void recolor3(TreeNode *node);
  void recolor4(TreeNode *node);
  void recolor5(TreeNode *node);
  void del(TreeNode *);
  void recolorDel(TreeNodeBase *node);
  void replace(TreeNode *, TreeNode *);
  void rotateLeft(TreeNodeBase *node);
  void rotateRight(TreeNodeBase *node);
  TreeNode *grandparent(TreeNode *);
  TreeNode *uncle(TreeNode *);
  TreeNode *sibling(TreeNode *);
  TreeNode *find(key_type, Compare cmp = Compare{});
  TreeNode *findMax(TreeNode *node) const;
  TreeNode *findMin(TreeNode *node) const;
  void deleteTree(TreeNode *);

 private:
  // void deleteTree(TreeNode *);
  void printIn(TreeNode *, int) const noexcept;
  TreeNode *copy(TreeNode *);
  TreeNode *root_;
  TreeNodeHeader head_;
};

// Constructor default
template <class K, class T, class Compare>
RBTree<K, T, Compare>::RBTree() noexcept : root_(nullptr){};

// Constructor with list initialize
template <class K, class T, class Compare>
RBTree<K, T, Compare>::RBTree(std::initializer_list<value_type> const &items)
    : RBTree() {
  for (auto i : items) {
    try {
      insertW(i.first, i.second);
    } catch (...) {
    }
  }
}

// Constructor copy
template <class K, class T, class Compare>
RBTree<K, T, Compare>::RBTree(const RBTree &other) : RBTree() {
  if (other.root_ != nullptr) {
    root_ = static_cast<TreeNode *>(copy(other.root_));
    head_.Init(root_);
    if (root_ != nullptr) root_->parent = (TreeNode *)&head_;
  }
}
// Constructor move
template <class K, class T, class Compare>
RBTree<K, T, Compare>::RBTree(RBTree &&other) noexcept : RBTree() {
  std::swap(root_, other.root_);
  std::swap(head_, other.head_);
  if (root_ != nullptr) root_->parent = (TreeNode *)&head_;
}

// Destructor  переписать без рекурсии
template <class K, class T, class Compare>
RBTree<K, T, Compare>::~RBTree() {
  head_.Init(nullptr);
  deleteTree(root_);
}

// Assignment copy
template <class K, class T, class Compare>
RBTree<K, T, Compare> &RBTree<K, T, Compare>::operator=(const RBTree &other) {
  if (this != &other) {
    if (root_ != nullptr) {
      head_.Init(nullptr);
      head_.count = 0;
      deleteTree(root_);
    }
    root_ = static_cast<TreeNode *>(copy(other.root_));
    head_.Init(root_);
    if (root_ != nullptr) root_->parent = (TreeNode *)&head_;
  }
  return *this;
}
// Copy
template <class K, class T, class Compare>
typename RBTree<K, T, Compare>::TreeNode *RBTree<K, T, Compare>::copy(
    TreeNode *node) {
  if (node == nullptr) return nullptr;
  TreeNode *new_node = new TreeNode(*node);
  ++head_.count;
  if (node->left != nullptr) {
    new_node->left = copy(static_cast<TreeNode *>(node->left));
    new_node->left->parent = new_node;
  }
  if (node->right != nullptr) {
    new_node->right = copy(static_cast<TreeNode *>(node->right));
    new_node->right->parent = new_node;
  }
  return new_node;
}

// Assignment move
template <class K, class T, class Compare>
RBTree<K, T, Compare> &RBTree<K, T, Compare>::operator=(RBTree &&other) {
  if (this != &other) {
    std::swap(root_, other.root_);
    std::swap(head_, other.head_);
    if (root_ != nullptr) root_->parent = (TreeNode *)&head_;
    if (other.root_ != nullptr) other.root_->parent = (TreeNode *)&other.head_;
  }
  return *this;
}

// Element access
// At
template <class K, class T, class Compare>
typename RBTree<K, T, Compare>::mapped_type &RBTree<K, T, Compare>::at(
    const K &k) {
  TreeNode *node = find(k);
  if (node != nullptr && node->key == k) {
    return node->value;
  } else {
    throw std::out_of_range("s21::map::at");
  }
}

// Operator[]
template <class K, class T, class Compare>
typename RBTree<K, T, Compare>::mapped_type &RBTree<K, T, Compare>::operator[](
    const K &k) {
  TreeNode *node = insertW(k, T());
  return node->value;
}

// Capasity
// Empty
template <class K, class T, class Compare>
bool RBTree<K, T, Compare>::empty() const noexcept {
  return (root_ == nullptr);
}

// Size
template <class K, class T, class Compare>
typename RBTree<K, T, Compare>::size_type RBTree<K, T, Compare>::size()
    const noexcept {
  return (root_ == nullptr) ? 0 : head_.count;
}

// Max size
template <class K, class T, class Compare>
typename RBTree<K, T, Compare>::size_type RBTree<K, T, Compare>::max_size()
    const noexcept {
  return (std::numeric_limits<size_type>::max() / 2 / sizeof(TreeNode));
}

// Modifiers
// Clear
template <class K, class T, class Compare>
void RBTree<K, T, Compare>::clear() noexcept {
  deleteTree(root_);
  root_ = nullptr;
  head_.Init(root_);
  head_.count = 0;
}

// Insert with std::pair
template <class K, class T, class Compare>
std::pair<typename RBTree<K, T, Compare>::iterator, bool>
RBTree<K, T, Compare>::insert(const value_type &val, Compare cmp) {
  TreeNode *p = find(val.first);
  if (p == nullptr) {
    root_ = new TreeNode(val.first, val.second);
    root_->parent = (TreeNode *)&head_;
    head_.Init(root_);
    ++head_.count;
    recolor(root_);
    return std::make_pair<iterator, bool>(root_, true);
  } else if (cmp(val.first, p->key) || cmp(p->key, val.first)) {
    try {
      TreeNode *n = new TreeNode(val.first, val.second);
      n->parent = p;
      ++head_.count;
      cmp(val.first, p->key) ? (p->left = n) : (p->right = n);
      recolor2(n);
      return std::make_pair<iterator, bool>(n, true);
    } catch (...) {
      std::cout << "No memory allocate\n";
      throw;
    }
  }
  return std::make_pair<iterator, bool>(p, false);
}

// Insert with K key and T value
template <class K, class T, class Compare>
std::pair<typename RBTree<K, T, Compare>::iterator, bool>
RBTree<K, T, Compare>::insert(const K &k, const T &v, Compare cmp) {
  TreeNode *p = find(k);
  if (p == nullptr) {
    root_ = new TreeNode(k, v);
    root_->parent = (TreeNode *)&head_;
    head_.Init(root_);
    ++head_.count;
    recolor(root_);
    return std::make_pair<iterator, bool>(root_, true);
  } else if (cmp(k, p->key) || cmp(p->key, k)) {
    try {
      TreeNode *n = new TreeNode(k, v);
      n->parent = p;
      ++head_.count;
      cmp(k, p->key) ? (p->left = n) : (p->right = n);
      recolor2(n);
      return std::make_pair<iterator, bool>(n, true);
    } catch (...) {
      std::cout << "No memory allocate\n";
      throw;
    }
  }
  return std::make_pair<iterator, bool>(p, false);
}

// Insert_or_assign
template <class K, class T, class Compare>
std::pair<typename RBTree<K, T, Compare>::iterator, bool>
RBTree<K, T, Compare>::insert_or_assign(const K &k, const T &v, Compare cmp) {
  TreeNode *p = find(k);
  try {
    if (p == nullptr) {
      root_ = new TreeNode(k, v);
      root_->parent = (TreeNode *)&head_;
      head_.Init(root_);
      ++head_.count;
      recolor(root_);
      return std::make_pair<iterator, bool>(root_, true);
    } else if (cmp(k, p->key)) {
      TreeNode *n = new TreeNode(k, v);
      n->parent = p;
      ++head_.count;
      p->left = n;
      recolor2(n);
      return std::make_pair<iterator, bool>(n, true);
    } else if (cmp(p->key, k)) {
      TreeNode *n = new TreeNode(k, v);
      n->parent = p;
      ++head_.count;
      p->right = n;
      recolor2(n);
      return std::make_pair<iterator, bool>(n, true);
    } else {
      p->value = v;
      return std::make_pair<iterator, bool>(p, false);
    }
  } catch (...) {
    std::cout << "No memory allocate\n";
    throw;
  }
}

// Erase
template <class K, class T, class Compare>
void RBTree<K, T, Compare>::erase(
    typename RBTree<K, T, Compare>::iterator pos) {
  TreeNode *node_delete = pos.getPtr();
  if (node_delete != nullptr && node_delete != (TreeNode *)&head_) {
    if (head_.count > 0) --(head_.count);
    if (node_delete->left != nullptr && node_delete->right != nullptr) {
      TreeNode *temp = findMax(static_cast<TreeNode *>(node_delete->left));
      std::swap(node_delete->key, temp->key);
      std::swap(node_delete->value, temp->value);
      del(temp);
    } else {
      del(node_delete);
    }
  }
}

// Swap
template <class K, class T, class Compare>
void RBTree<K, T, Compare>::swap(RBTree &other) noexcept {
  std::swap(root_, other.root_);
  std::swap(head_, other.head_);
  if (root_ != nullptr) root_->parent = (TreeNode *)&head_;
  if (other.root_ != nullptr) other.root_->parent = (TreeNode *)&other.head_;
}

// Merge
template <class K, class T, class Compare>
void RBTree<K, T, Compare>::merge(RBTree &other) {
  if (other.root_ != nullptr && this != &other) {
    if (root_ == nullptr) {
      swap(other);
    } else {
      RBTree temp(std::move(other));
      getNode(temp.root_, other);
      temp.root_ = nullptr;
    }
  }
}
// getNode get leaf
template <class K, class T, class Compare>
void RBTree<K, T, Compare>::getNode(TreeNode *node, RBTree &other) {
  if (node->left != nullptr)
    getNode(static_cast<TreeNode *>(node->left), other);
  if (node->right != nullptr)
    getNode(static_cast<TreeNode *>(node->right), other);
  insert(node, other);
}
// Insert for merge
template <class K, class T, class Compare>
void RBTree<K, T, Compare>::insert(TreeNode *node, RBTree &other, Compare cmp) {
  if (node != nullptr) {
    node->left = node->right = nullptr;
    node->color = kRed;
    TreeNode *p = find(node->key);
    if (p == nullptr) {
      root_ = node;
      root_->parent = &(head_.header);
      head_.count = 1;
      head_.Init(root_);
      recolor(root_);
    } else if (cmp(node->key, p->key)) {
      node->parent = p;
      p->left = node;
      ++head_.count;
      recolor2(node);
    } else if (cmp(p->key, node->key)) {
      node->parent = p;
      p->right = node;
      ++head_.count;
      recolor2(node);
    } else {
      other.insert(node, other);
    }
  }
}

// Lookup
template <class K, class T, class Compare>
bool RBTree<K, T, Compare>::contains(const K &k, Compare cmp) {
  TreeNode *temp = root_;
  for (; temp != nullptr;) {
    if (cmp(k, temp->key)) {
      temp = static_cast<TreeNode *>(temp->left);
    } else if (cmp(temp->key, k)) {
      temp = static_cast<TreeNode *>(temp->right);
    } else {
      return true;
    }
  }
  return false;
}
// InsertW
template <class K, class T, class Compare>
typename RBTree<K, T, Compare>::TreeNode *RBTree<K, T, Compare>::insertW(
    K k, T v, Compare cmp) {
  TreeNode *p = find(k);
  if (p == nullptr) {
    root_ = new TreeNode(k, v);
    root_->parent = (TreeNode *)&head_;
    head_.Init(root_);
    ++head_.count;
    recolor(root_);
    return root_;
  } else if (cmp(k, p->key) || cmp(p->key, k)) {
    try {
      TreeNode *n = new TreeNode(k, v);
      n->parent = p;
      ++head_.count;
      cmp(k, p->key) ? (p->left = n) : (p->right = n);
      recolor2(n);
      return n;
    } catch (...) {
      std::cout << "No memory allocate\n";
    }
  }
  return p;
}

// RotateLeft
template <class K, class T, class Compare>
void RBTree<K, T, Compare>::rotateLeft(TreeNodeBase *node) {
  TreeNodeBase *temp = node->right;
  temp->parent = node->parent;
  if (node->parent != &head_.header) {
    if (node->parent->left == node)
      node->parent->left = temp;
    else
      node->parent->right = temp;
  } else {
    root_ = static_cast<TreeNode *>(temp);
    head_.Init(temp);
  }
  node->right = temp->left;
  if (temp->left != nullptr) temp->left->parent = node;
  node->parent = temp;
  temp->left = node;
}

// RotateRight
template <class K, class T, class Compare>
void RBTree<K, T, Compare>::rotateRight(TreeNodeBase *node) {
  TreeNodeBase *temp = node->left;
  temp->parent = node->parent;
  if (node->parent != &head_.header) {
    if (node->parent->left == node)
      node->parent->left = temp;
    else
      node->parent->right = temp;
  } else {
    root_ = static_cast<TreeNode *>(temp);
    head_.Init(temp);
  }
  node->left = temp->right;
  if (temp->right != nullptr) temp->right->parent = node;
  node->parent = temp;
  temp->right = node;
}

// Recolor
template <class K, class T, class Compare>
void RBTree<K, T, Compare>::recolor(TreeNode *node) {
  if (node->parent == &head_.header) {
    node->color = kBlack;
  } else {
    recolor2(node);
  }
}
// Recolor2
template <class K, class T, class Compare>
void RBTree<K, T, Compare>::recolor2(TreeNode *node) {
  if (node->parent->color != kBlack) recolor3(node);
}
// Recolor3
template <class K, class T, class Compare>
void RBTree<K, T, Compare>::recolor3(TreeNode *node) {
  TreeNode *gp = grandparent(node), *u = uncle(node);
  if (u != nullptr && u->color == kRed) {
    node->parent->color = kBlack;
    u->color = kBlack;
    gp->color = kRed;
    recolor(gp);
  } else {
    recolor4(node);
  }
}
// Recolor4
template <class K, class T, class Compare>
void RBTree<K, T, Compare>::recolor4(TreeNode *node) {
  TreeNode *gp = grandparent(node);
  if (node == node->parent->right && node->parent == gp->left) {
    rotateLeft(node->parent);
    node = static_cast<TreeNode *>(node->left);
  } else if (node == node->parent->left && node->parent == gp->right) {
    rotateRight(node->parent);
    node = static_cast<TreeNode *>(node->right);
  }
  recolor5(node);
}
// Recolor5
template <class K, class T, class Compare>
void RBTree<K, T, Compare>::recolor5(TreeNode *node) {
  TreeNode *gp = grandparent(node);
  node->parent->color = kBlack;
  gp->color = kRed;
  if (node == node->parent->left && node->parent == gp->left) {
    rotateRight(gp);
  } else {
    rotateLeft(gp);
  }
}

// Replace
template <class K, class T, class Compare>
void RBTree<K, T, Compare>::replace(TreeNode *node, TreeNode *child) {
  if (child != nullptr) child->parent = node->parent;
  if (node->parent != (TreeNode *)&head_) {
    if (node == node->parent->left) {
      node->parent->left = child;
    } else {
      node->parent->right = child;
    }
  } else {
    root_ = child;
    head_.Init(child);
  }
}

// Del
template <class K, class T, class Compare>
void RBTree<K, T, Compare>::del(TreeNode *node) {
  TreeNode *child = static_cast<TreeNode *>(
      (node->left != nullptr) ? node->left : node->right);
  if (node->color == kBlack) {
    if (child != nullptr && child->color == kRed) {
      child->color = kBlack;
    } else {
      recolorDel(node);
    }
  }
  replace(node, child);
  delete node;
}

// RecolorDel
template <class K, class T, class Compare>
void RBTree<K, T, Compare>::recolorDel(TreeNodeBase *node) {
  TreeNodeBase *s = sibling(static_cast<TreeNode *>(node));
  if (node->parent == &head_.header) {
  } else if (!isBlack(s)) {
    node->parent->color = kRed;
    s->color = kBlack;
    if (node == node->parent->left)
      rotateLeft(node->parent);
    else
      rotateRight(node->parent);
    recolorDel(node);
  } else if (isBlack(node->parent) && isBlack(s) && isBlack(s->left) &&
             isBlack(s->right)) {
    s->color = kRed;
    recolorDel(node->parent);
  } else if (!isBlack(node->parent) && isBlack(s) && isBlack(s->left) &&
             isBlack(s->right)) {
    s->color = kRed;
    node->parent->color = kBlack;
  } else if (node == node->parent->left && isBlack(s->right) &&
             !isBlack(s->left)) {
    s->color = kRed;
    s->left->color = kBlack;
    rotateRight(s);
    recolorDel(node);
  } else if (node == node->parent->right && isBlack(s->left) &&
             !isBlack(s->right)) {
    s->color = kRed;
    s->right->color = kBlack;
    rotateLeft(s);
    recolorDel(node);
  } else {
    s->color = node->parent->color;
    node->parent->color = kBlack;
    if (node == node->parent->left) {
      s->right->color = kBlack;
      rotateLeft(node->parent);
    } else {
      s->left->color = kBlack;
      rotateRight(node->parent);
    }
  }
}

// IsBlack
template <class K, class T, class Compare>
inline bool RBTree<K, T, Compare>::isBlack(TreeNodeBase *node) const noexcept {
  return (node == nullptr || node->color == kBlack);
};

// Grandparent
template <class K, class T, class Compare>
typename RBTree<K, T, Compare>::TreeNode *RBTree<K, T, Compare>::grandparent(
    TreeNode *node) {
  if (node != nullptr && node->parent != nullptr) {
    return static_cast<TreeNode *>(node->parent->parent);
  } else {
    return nullptr;
  }
}

// Uncle
template <class K, class T, class Compare>
typename RBTree<K, T, Compare>::TreeNode *RBTree<K, T, Compare>::uncle(
    TreeNode *node) {
  TreeNode *gp = grandparent(node);
  if (gp == nullptr) {
    return nullptr;
  } else if (node->parent == gp->left) {
    return static_cast<TreeNode *>(gp->right);
  } else {
    return static_cast<TreeNode *>(gp->left);
  }
}

// Sibling
template <class K, class T, class Compare>
typename RBTree<K, T, Compare>::TreeNode *RBTree<K, T, Compare>::sibling(
    TreeNode *node) {
  if (node->parent == nullptr) {
    return nullptr;
  } else if (node == static_cast<TreeNode *>(node->parent->left)) {
    return static_cast<TreeNode *>(node->parent->right);
  } else {
    return static_cast<TreeNode *>(node->parent->left);
  }
}

// find (node by key)
template <class K, class T, class Compare>
typename RBTree<K, T, Compare>::TreeNode *RBTree<K, T, Compare>::find(
    K k, Compare cmp) {
  TreeNode *temp = this->root_, *p = this->root_;
  while (temp != nullptr) {
    p = temp;
    if (cmp(k, temp->key)) {
      temp = static_cast<TreeNode *>(temp->left);
    } else if (cmp(temp->key, k)) {
      temp = static_cast<TreeNode *>(temp->right);
    } else {
      temp = nullptr;
    }
  }
  return p;
}

// FindMax
template <class K, class T, class Compare>
typename RBTree<K, T, Compare>::TreeNode *RBTree<K, T, Compare>::findMax(
    TreeNode *node) const {
  TreeNodeBase *p = node;
  for (TreeNodeBase *temp = p; temp != nullptr; p = temp, temp = temp->right) {
  }
  return static_cast<TreeNode *>(p);
}

// FindMin
template <class K, class T, class Compare>
typename RBTree<K, T, Compare>::TreeNode *RBTree<K, T, Compare>::findMin(
    TreeNode *node) const {
  TreeNodeBase *p = node;
  for (TreeNodeBase *temp = p; temp != nullptr; p = temp, temp = temp->left) {
  }
  return static_cast<TreeNode *>(p);
}

// DeleteTree
template <class K, class T, class Compare>
void RBTree<K, T, Compare>::deleteTree(TreeNode *node) {
  if (node != nullptr) {
    deleteTree(static_cast<TreeNode *>(node->left));
    deleteTree(static_cast<TreeNode *>(node->right));
    delete node;
  }
}
// Print
template <class K, class T, class Compare>
inline void RBTree<K, T, Compare>::print() const noexcept {
  printIn(root_, 0);
}

// PrintIn
template <class K, class T, class Compare>
void RBTree<K, T, Compare>::printIn(TreeNode *node, int d) const noexcept {
  if (node != nullptr) {
    printIn(static_cast<TreeNode *>(node->left), d + 1);
    for (int i = d; i > 0; --i) std::cout << "\t";
    std::cout << node->key << "-" << node->value << "("
              << (node->color ? 'b' : 'r') << ")" << '\n';
    printIn(static_cast<TreeNode *>(node->right), d + 1);
  }
};
// begin
template <class K, class T, class Compare>
typename RBTree<K, T, Compare>::iterator RBTree<K, T, Compare>::begin() {
  return (root_ == nullptr) ? iterator((TreeNode *)&head_)
                            : iterator(findMin(root_));
};

// end
template <class K, class T, class Compare>
typename RBTree<K, T, Compare>::iterator RBTree<K, T, Compare>::end() {
  return iterator((TreeNode *)&head_);
};

}  // end namespace s21
#endif  // _S21_CONTAINERS_S21_RBTREE_H_
