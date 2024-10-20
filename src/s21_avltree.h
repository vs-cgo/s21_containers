#ifndef TREENODE_H_
#define TREENODE_H_

#include <initializer_list>
#include <iostream>
#include <limits>
#include <vector>

namespace s21 {
template <class K, class Compare = std::less<K>>
class BinaryTree {
 public:
  using key_type = K;
  using value_type = K;
  using size_type = size_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  struct TreeNode {
    TreeNode *_parent;
    TreeNode *_left;
    TreeNode *_right;
    value_type value;
    size_type sizes;
    int _height;

    explicit TreeNode(value_type v)
        : _parent(nullptr),
          _left(nullptr),
          _right(nullptr),
          value(v),
          sizes(1),
          _height(1){};
    TreeNode(TreeNode &other)
        : _parent(other._parent),
          _left(other._left),
          _right(other._right),
          value(other.value),
          sizes(other.sizes),
          _height(other._height){};
  };

  BinaryTree();
  explicit BinaryTree(value_type v);
  BinaryTree(std::initializer_list<value_type> const &items);
  BinaryTree(const BinaryTree &other);
  BinaryTree(BinaryTree &&other);
  ~BinaryTree();

  BinaryTree &operator=(const BinaryTree &other);
  BinaryTree &operator=(BinaryTree &&other);

  void print();

  TreeNode *copy(TreeNode *root);

 public:
  class Iterator {
   public:
    using tree = BinaryTree<K, Compare>::TreeNode;
    Iterator() : node(nullptr){};
    explicit Iterator(tree *node);
    Iterator(tree *node, tree *root);
    Iterator(const Iterator &other);
    ~Iterator();

    tree *get();
    value_type operator*() const;
    Iterator &operator++();
    Iterator &operator--();
    tree *minusMinus(tree *node);
    tree *plusPlus(tree *node);
    bool operator==(const Iterator &other) { return node == other.node; };
    bool operator!=(const Iterator &other) { return node != other.node; };

   protected:
    tree *node;
    tree *root;
  };

  class Const_iterator : public Iterator {
   public:
    using tree = BinaryTree<K, Compare>::TreeNode;
    tree *ptr;
    Const_iterator();
    explicit Const_iterator(const tree *p);
    ~Const_iterator();
  };

 public:
  using iterator = Iterator;
  using const_iterator = Const_iterator;

  std::pair<iterator, bool> insert(const value_type &value);
  TreeNode *insert(TreeNode *root, value_type v, TreeNode **p);
  iterator insert_for_multiset(const value_type &value);
  TreeNode *insert_for_multiset(TreeNode *root, value_type v, TreeNode **p);
  std::pair<iterator, bool> insert_many_for_multiset(const value_type &value);
  void erase(iterator pos);
  TreeNode *erase(TreeNode *p, value_type v);
  iterator find(const K &key);
  bool contains(const value_type &value);
  iterator find(TreeNode *root, value_type v);
  TreeNode *_find(TreeNode *root, value_type v);
  TreeNode *findMin(TreeNode *node);
  TreeNode *delMin(TreeNode *node);
  iterator findMin();
  iterator findMax();
  iterator end();
  iterator begin();

  int height(TreeNode *p);
  int bfactor(TreeNode *p);
  void fixheight(TreeNode *p);
  TreeNode *rotateright(TreeNode *p);
  TreeNode *rotateleft(TreeNode *p);
  TreeNode *balance(TreeNode *p);
  TreeNode *findmax(TreeNode *p);

  size_type check_size(TreeNode *root);
  void clear();
  void swap(BinaryTree &other);
  size_type size();
  TreeNode *get_root();
  bool empty();
  size_type max_size();
  void merge(BinaryTree &other);
  void merge_for_multiset(BinaryTree &other);
  size_type count(const key_type &k);
  iterator lower_bound(const key_type &key);
  iterator upper_bound(const key_type &key);
  std::pair<iterator, iterator> equal_range(const key_type &key);

 private:
  TreeNode *_root;
  void printTree(TreeNode *root);
  void deleteTree(TreeNode *ptr);
};

//-----Конструкторы-----
template <typename K, typename Compare>
BinaryTree<K, Compare>::BinaryTree() : _root(nullptr){};

template <typename K, typename Compare>
BinaryTree<K, Compare>::BinaryTree(value_type v) {
  _root = new TreeNode(v);
};

template <typename K, typename Compare>
BinaryTree<K, Compare>::BinaryTree(
    std::initializer_list<value_type> const &items)
    : BinaryTree(*(items.begin())) {
  for (auto i = (items.begin()) + 1; i < items.end(); i++) {
    insert(*i);
  }
};

template <typename K, typename Compare>
BinaryTree<K, Compare>::BinaryTree(const BinaryTree &other)
    : BinaryTree(other._root->value) {
  if (other._root->_left) {
    _root->_left = copy(other._root->_left);
  }
  if (other._root->_right) {
    _root->_right = copy(other._root->_right);
  }
  this->_root->sizes = other._root->sizes;
};

template <typename K, typename Compare>
BinaryTree<K, Compare>::BinaryTree(BinaryTree &&other) : BinaryTree() {
  std::swap(_root, other._root);
};
//-----Деструктор-----
template <typename K, typename Compare>
BinaryTree<K, Compare>::~BinaryTree() {
  deleteTree(_root);
};
//-----Операторы-----
template <typename K, typename Compare>
BinaryTree<K, Compare> &BinaryTree<K, Compare>::operator=(
    const BinaryTree &other) {
  if (this != &other) {
    deleteTree(_root);
    this->_root = copy(other._root);
  }
  return *this;
};

template <typename K, typename Compare>
BinaryTree<K, Compare> &BinaryTree<K, Compare>::operator=(BinaryTree &&other) {
  if (this != &other) {
    std::swap(this->_root, other._root);
    other.clear();
  }
  return *this;
};
//-----Копирование-----
template <typename K, typename Compare>
typename BinaryTree<K, Compare>::TreeNode *BinaryTree<K, Compare>::copy(
    TreeNode *root) {
  if (!root) return nullptr;
  TreeNode *newTreeNode = new TreeNode(*root);
  if (root->_left) {
    newTreeNode->_left = copy(root->_left);
  }
  if (root->_right) {
    newTreeNode->_right = copy(root->_right);
  }
  return newTreeNode;
};
//-----Печать дерева-----
template <typename K, typename Compare>
void BinaryTree<K, Compare>::print() {
  printTree(_root);
  std::cout << '\n';
};
// -----Итераторы-----
template <typename K, typename Compare>
BinaryTree<K, Compare>::Iterator::Iterator(tree *node) : node(node){};

template <typename K, typename Compare>
BinaryTree<K, Compare>::Iterator::Iterator(tree *node, tree *root)
    : node(node), root(root){};

template <typename K, typename Compare>
BinaryTree<K, Compare>::Iterator::Iterator(const Iterator &other) {
  this->node = other.node;
  this->root = other.root;
}

template <typename K, typename Compare>
BinaryTree<K, Compare>::Iterator::~Iterator() {
  if (node) node = nullptr;
  if (root) root = nullptr;
}

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::Iterator::tree *
BinaryTree<K, Compare>::Iterator::get() {
  return node;
};

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::iterator BinaryTree<K, Compare>::begin() {
  return iterator(findMin(get_root()), get_root());
}

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::value_type
BinaryTree<K, Compare>::Iterator::operator*() const {
  return node->value;
};

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::Iterator &
BinaryTree<K, Compare>::Iterator::operator++() {
  tree *p = root;
  if (!node) {
    while (p->_left) p = p->_left;
    node = p;
    return *this;
  } else {
    node = plusPlus(node);
  }
  return *this;
};

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::Iterator::tree *
BinaryTree<K, Compare>::Iterator::plusPlus(tree *node) {
  if (node->_right) {
    node = node->_right;
    while (node->_left) node = node->_left;
  } else {
    TreeNode *parent = node->_parent;
    while (parent && node == parent->_right) {
      node = parent;
      parent = parent->_parent;
    }
    node = parent;
  }
  return node;
}

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::Iterator &
BinaryTree<K, Compare>::Iterator::operator--() {
  tree *p = root;
  if (!node) {
    while (p->_right) p = p->_right;
    node = p;
    return *this;
  } else {
    node = minusMinus(node);
  }
  return *this;
};

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::Iterator::tree *
BinaryTree<K, Compare>::Iterator::minusMinus(tree *node) {
  if (node->_left) {
    node = node->_left;
    while (node->_right) node = node->_right;
  } else {
    TreeNode *parent = node->_parent;
    while (parent && node == parent->_left) {
      node = parent;
      parent = parent->_parent;
    }
    node = parent;
  }
  return node;
};

//-----КонстИтераторы-----
template <typename K, typename Compare>
BinaryTree<K, Compare>::Const_iterator::Const_iterator() : Iterator(){};

template <typename K, typename Compare>
BinaryTree<K, Compare>::Const_iterator::Const_iterator(const tree *p)
    : Iterator(p){};

template <typename K, typename Compare>
BinaryTree<K, Compare>::Const_iterator::~Const_iterator() {
  if (ptr) ptr = nullptr;
};
//-----Инсерты-----
template <typename K, typename Compare>
std::pair<typename BinaryTree<K, Compare>::iterator, bool>
BinaryTree<K, Compare>::insert(const value_type &value) {
  TreeNode *p = nullptr;
  _root = insert(this->get_root(), value, &p);
  if (p != nullptr) {
    return std::make_pair(iterator(p), true);
  }
  return std::make_pair(iterator(p), false);
}

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::TreeNode *BinaryTree<K, Compare>::insert(
    TreeNode *root, value_type v, TreeNode **p) {
  if (!root) {
    return *p = new TreeNode(v);
  }
  if (v < root->value) {
    root->_left = insert(root->_left, v, p);
    root->_left->_parent = root;
  } else {
    if (v > root->value) {
      root->_right = insert(root->_right, v, p);
      root->_right->_parent = root;
    }
  }
  return balance(root);
};

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::iterator
BinaryTree<K, Compare>::insert_for_multiset(const value_type &value) {
  TreeNode *p = nullptr;
  _root = insert_for_multiset(_root, value, &p);
  return iterator(p);
}

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::TreeNode *
BinaryTree<K, Compare>::insert_for_multiset(TreeNode *root, value_type v,
                                            TreeNode **p) {
  if (!root) {
    return *p = new TreeNode(v);
  }
  if (v < root->value) {
    root->_left = insert_for_multiset(root->_left, v, p);
    root->_left->_parent = root;
  } else {
    root->_right = insert_for_multiset(root->_right, v, p);
    root->_right->_parent = root;
  }
  return balance(root);
};

template <typename K, typename Compare>
std::pair<typename BinaryTree<K, Compare>::iterator, bool>
BinaryTree<K, Compare>::insert_many_for_multiset(const value_type &value) {
  TreeNode *p = nullptr;
  _root = insert_for_multiset(this->get_root(), value, &p);
  if (p != nullptr) {
    return std::make_pair(iterator(p), true);
  }
  return std::make_pair(iterator(p), false);
};
//-----ПоискУзла-----
template <typename K, typename Compare>
typename BinaryTree<K, Compare>::iterator BinaryTree<K, Compare>::find(
    const K &key) {
  TreeNode *node = _find(get_root(), key);
  return iterator(node);
};

template <typename K, typename Compare>
bool BinaryTree<K, Compare>::contains(const value_type &value) {
  return _find(get_root(), value) ? true : false;
};

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::iterator BinaryTree<K, Compare>::find(
    TreeNode *root, value_type v) {
  if (!root) return iterator(nullptr);
  if (root->value == v) return iterator(root);
  if (root->value > v)
    return find(root->_left, v);
  else
    return find(root->_right, v);
};

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::TreeNode *BinaryTree<K, Compare>::_find(
    TreeNode *root, value_type v) {
  if (!root) return nullptr;
  if (root->value == v) return root;
  if (root->value > v)
    return _find(root->_left, v);
  else
    return _find(root->_right, v);
}

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::TreeNode *BinaryTree<K, Compare>::findMin(
    TreeNode *node) {
  return node->_left ? findMin(node->_left) : node;
};

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::TreeNode *BinaryTree<K, Compare>::delMin(
    TreeNode *node) {
  if (!node->_left)
    return node->_right;
  else
    node->_left = delMin(node->_left);
  return balance(node);
};

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::iterator BinaryTree<K, Compare>::findMin() {
  TreeNode *p = this->_root;
  while (p->_left) {
    p = p->_left;
  }
  return iterator(p);
};

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::iterator BinaryTree<K, Compare>::findMax() {
  TreeNode *p = this->_root;
  while (p->_right) {
    p = p->_right;
  }
  return iterator(p);
};

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::iterator BinaryTree<K, Compare>::end() {
  return iterator(nullptr, get_root());
};

//-----АвлДерево-----
template <typename K, typename Compare>
int BinaryTree<K, Compare>::height(TreeNode *p) {
  return p == nullptr ? 0 : p->_height;
};

template <typename K, typename Compare>
int BinaryTree<K, Compare>::bfactor(TreeNode *p) {
  return p ? (height(p->_left) - height(p->_right)) : 0;
};

template <typename K, typename Compare>
void BinaryTree<K, Compare>::fixheight(TreeNode *p) {
  int left_height = height(p->_left);
  int right_height = height(p->_right);
  p->_height = (left_height > right_height ? left_height : right_height) + 1;
};

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::TreeNode *BinaryTree<K, Compare>::balance(
    TreeNode *p) {
  fixheight(p);
  if (bfactor(p) > 1) {
    if (bfactor(p->_left) < 0) {
      p->_left = rotateright(p->_left);
    }
    return rotateleft(p);
  }
  if (bfactor(p) < -1) {
    if (bfactor(p->_right) > 0) {
      p->_right = rotateleft(p->_right);
    }
    return rotateright(p);
  }
  return p;
};

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::TreeNode *BinaryTree<K, Compare>::rotateleft(
    TreeNode *p) {
  TreeNode *q = p->_left;
  q->_parent = p->_parent;
  p->_left = q->_right;
  if (p->_left) p->_left->_parent = p;
  q->_right = p;
  p->_parent = q;
  fixheight(p);
  fixheight(q);
  return q;
};

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::TreeNode *BinaryTree<K, Compare>::rotateright(
    TreeNode *p) {
  TreeNode *q = p->_right;
  q->_parent = p->_parent;
  p->_right = q->_left;
  if (p->_right) p->_right->_parent = p;
  q->_left = p;
  p->_parent = q;
  fixheight(p);
  fixheight(q);
  return q;
};

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::TreeNode *BinaryTree<K, Compare>::findmax(
    TreeNode *p) {
  if (!p) return nullptr;
  if (!p->_right)
    return p;
  else
    return findmax(p->_right);
};

template <typename K, typename Compare>
void BinaryTree<K, Compare>::erase(iterator pos) {
  value_type v = pos.get()->value;
  _root = erase(get_root(), v);
}

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::TreeNode *BinaryTree<K, Compare>::erase(
    TreeNode *node, value_type v) {
  if (node == nullptr) return 0;
  if (v < node->value) node->_left = erase(node->_left, v);
  if (v > node->value) node->_right = erase(node->_right, v);
  if (v == node->value) {
    TreeNode *left = node->_left;
    TreeNode *right = node->_right;
    TreeNode *parent = node->_parent;
    if (left) left->_parent = parent;
    if (right) right->_parent = parent;
    delete node;
    node = nullptr;
    if (!right) {
      return left;
    }
    TreeNode *min = findMin(right);
    min->_parent = parent;
    min->_right = delMin(right);
    if (min->_right) min->_right->_parent = min;
    min->_left = left;
    if (min->_left) min->_left->_parent = min;
    return balance(min);
  }
  return balance(node);
};

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::size_type BinaryTree<K, Compare>::check_size(
    TreeNode *root) {
  if (!root) return 0;
  if (root->_left) root->sizes += check_size(root->_left);
  if (root->_right) root->sizes += check_size(root->_right);
  return root->sizes;
};

template <typename K, typename Compare>
void BinaryTree<K, Compare>::clear() {
  if (!this->empty()) deleteTree(_root);
  _root = nullptr;
};

template <typename K, typename Compare>
void BinaryTree<K, Compare>::swap(BinaryTree &other) {
  std::swap(this->_root, other._root);
};

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::size_type BinaryTree<K, Compare>::size() {
  return check_size(get_root());
};

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::TreeNode *BinaryTree<K, Compare>::get_root() {
  return _root;
};

template <typename K, typename Compare>
bool BinaryTree<K, Compare>::empty() {
  return this->size() ? false : true;
};

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::size_type BinaryTree<K, Compare>::max_size() {
  return (std::numeric_limits<size_type>::max() / sizeof(value_type) / 2 / 10);
};

template <typename K, typename Compare>
void BinaryTree<K, Compare>::merge(BinaryTree &other) {
  if (_root == other._root) return;
  BinaryTree<K, Compare> tmp;
  auto it = other.begin();
  for (; it != other.end(); ++it) {
    if (!insert(*it).second) tmp.insert(*it);
  }
  other = tmp;
};

template <typename K, typename Compare>
void BinaryTree<K, Compare>::merge_for_multiset(BinaryTree &other) {
  if (_root == other._root) return;
  auto it = other.begin();
  for (; it != other.end(); ++it) {
    insert_for_multiset(*it);
  }
  other.clear();
};

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::size_type BinaryTree<K, Compare>::count(
    const key_type &k) {
  size_type c = 0;
  auto it = this->begin();
  for (; it != this->end(); ++it) {
    if (k == *it) ++c;
  }
  return c;
};

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::iterator BinaryTree<K, Compare>::lower_bound(
    const key_type &key) {
  auto it = this->begin();
  for (; (it != this->end()) && (*it < key); ++it)
    ;
  return it;
};

template <typename K, typename Compare>
typename BinaryTree<K, Compare>::iterator BinaryTree<K, Compare>::upper_bound(
    const key_type &key) {
  auto it = this->begin();
  for (; it != this->end(); ++it)
    if (*it > key) break;
  return it;
};

template <typename K, typename Compare>
std::pair<typename BinaryTree<K, Compare>::iterator,
          typename BinaryTree<K, Compare>::iterator>
BinaryTree<K, Compare>::equal_range(const key_type &key) {
  return std::make_pair(lower_bound(key), upper_bound(key));
};

template <typename K, typename Compare>
void BinaryTree<K, Compare>::printTree(TreeNode *root) {
  if (root) {
    printTree(root->_left);
    std::cout << root->value << ' ';
    printTree(root->_right);
  }
};

template <typename K, typename Compare>
void BinaryTree<K, Compare>::deleteTree(TreeNode *ptr) {
  if (ptr) {
    deleteTree(ptr->_left);
    deleteTree(ptr->_right);
    delete ptr;
  }
};

}  // namespace s21
#endif  // TREENODE_H_