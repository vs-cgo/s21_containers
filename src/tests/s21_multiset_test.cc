#include "../s21_multiset.h"

#include <gtest/gtest.h>

TEST(MultisetTest, Cons1) {
  s21::Multiset<int> a;
  std::multiset<int> b;
  ASSERT_EQ(a.empty(), true);
  ASSERT_EQ(b.empty(), true);
}

TEST(MultisetTest, Cons2andIter) {
  s21::Multiset<int> a(
      {2342, 234, 178, -789, 478, 478, 478, 0, -234234, 89, 89, 89});
  std::multiset<int> b(
      {2342, 234, 178, -789, 478, 478, 478, 0, -234234, 89, 89, 89});
  s21::Multiset<int>::iterator i = a.begin();
  std::multiset<int>::iterator it = b.begin();
  for (int k = 0; k < 8; ++i, ++it, ++k) {
    ASSERT_EQ(*i, *it);
  };
}

TEST(MultisetTest, Cons3andIter) {
  s21::Multiset<int> a(
      {2342, 234, 178, -789, 478, 478, 478, 0, -234234, 89, 89, 89});
  s21::Multiset<int> b(a);
  s21::Multiset<int>::iterator i = a.begin();
  s21::Multiset<int>::iterator it = b.begin();
  for (int k = 0; k < 8; ++i, ++it, ++k) {
    ASSERT_EQ(*i, *it);
  };
}

TEST(MultisetTest, MoveConstructor) {
  s21::Multiset<int> a = {1, 2, 2, 3, 3, 3};
  s21::Multiset<int> b = {1, 2, 2, 3, 3, 3};
  s21::Multiset<int> c(std::move(a));
  s21::Multiset<int>::iterator i = b.begin();
  s21::Multiset<int>::iterator it = c.begin();
  for (int k = 0; k < 6; ++i, ++it, ++k) {
    ASSERT_EQ(*i, *it);
  };
  ASSERT_EQ(a.empty(), true);
}

TEST(MultisetTest, Destructor) {
  s21::Multiset<int>* a = new s21::Multiset<int>({1, 2, 2, 3, 3, 3});
  delete a;
  SUCCEED();
}

TEST(MultisetTest, Move) {
  s21::Multiset<int> s1;
  s1.insert(1);
  s1.insert(2);
  s1.insert(3);
  s21::Multiset<int> s2;
  s2.insert(4);
  s2.insert(5);
  s2 = std::move(s1);
  EXPECT_EQ(s2.size(), 3ULL);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
  EXPECT_EQ(s1.size(), 0ULL);
  EXPECT_FALSE(s1.contains(1));
  EXPECT_FALSE(s1.contains(2));
  EXPECT_FALSE(s1.contains(3));
}

TEST(MultisetTest, Iterators) {
  s21::Multiset<int> a = {1, 2, 2, 3, 3, 3};
  std::vector<int> b = {1, 2, 2, 3, 3, 3};
  int i = 0;
  for (auto it = a.begin(); it != a.end(); ++it) {
    ASSERT_EQ(*it, b[i++]);
  }
}

TEST(MultisetTest, Insert) {
  s21::Multiset<int> a = {1, 2, 2, 3, 3, 3};
  a.insert(25);
  a.insert(-789);
  ASSERT_EQ(a.size(), 8UL);
  ASSERT_EQ(a.count(2), 2UL);
  ASSERT_EQ(a.count(3), 3UL);
  ASSERT_EQ(a.count(25), 1UL);
  ASSERT_EQ(a.count(-789), 1UL);
}

TEST(MultisetTest, Clear) {
  s21::Multiset<int> a = {1, 2, 2, 3, 3, 3};
  a.clear();
  size_t i = 0;
  ASSERT_EQ(a.size(), i);
}

TEST(MultisetTest, Erase) {
  s21::Multiset<int> a = {1, 2, 2, 2, 3, 3, 3};
  std::multiset<int> b = {1, 2, 2, 2, 3, 3, 3};
  s21::Multiset<int>::iterator c = a.begin();
  ++c;
  std::multiset<int>::iterator d = b.begin();
  ++d;
  a.erase(c);
  b.erase(d);
  ASSERT_EQ(a.size(), b.size());
  ASSERT_EQ(a.count(2), b.count(2));
}

TEST(MultisetTest, MaxSize) {
  s21::Multiset<int> a;
  std::multiset<int> b;
  ASSERT_EQ(a.max_size(), b.max_size());
}

TEST(MultisetTest, Erase1) {
  s21::Multiset<int> a = {-2343, -123, -12, 5, 34, 234, 12900};
  s21::Multiset<int>::iterator c = a.begin();
  ++c;
  ++c;
  ++c;
  a.erase(c);
  s21::Multiset<int>::iterator b = a.begin();
  std::vector<int> k{-2343, -123, -12, 34, 234, 12900};
  size_t i = 0;
  for (; b != a.end(); ++b, ++i) ASSERT_EQ(*b, k[i]);
  ASSERT_EQ(a.size(), 6ULL);
}

TEST(MultisetTest, Swap) {
  s21::Multiset<int> a = {1, 2, 3, 3, 3, 3, 56};
  s21::Multiset<int> b = {2, 3, 3, 5, 5, 5, 78};
  std::vector<int> d = {2, 3, 3, 5, 5, 5, 78};
  a.swap(b);
  size_t i = 0;
  auto it = a.begin();
  for (; it != a.end(); ++it, ++i) {
    ASSERT_EQ(*it, d[i]);
  }
}

TEST(MultisetTest, Merge) {
  s21::Multiset<char> a = {'a', 'a', 'b', 'b'};
  s21::Multiset<char> b = {'c', 'c', 'd', 'd'};
  std::vector<char> d = {'a', 'a', 'b', 'b', 'c', 'c', 'd', 'd'};
  a.merge(b);
  size_t i = 0;
  auto it = a.begin();
  for (; it != a.end(); ++it, ++i) {
    ASSERT_EQ(*it, d[i]);
  }
}

TEST(MultisetTest, Find) {
  s21::Multiset<std::string> a = {"Hello!", "Byyy", "Fooo", "Hello"};
  std::multiset<std::string> b = {"Hello!", "Byyy", "Fooo", "Hello"};
  s21::Multiset<std::string>::iterator c = a.find("Fooo");
  std::multiset<std::string>::iterator d = b.find("Fooo");
  ASSERT_EQ(*c, *d);
}

TEST(MultisetTest, Contains) {
  s21::Multiset<std::string> a = {"Hello!", "Byyy", "Fooo", "Hello"};
  ASSERT_EQ(a.contains("ggg"), false);
  ASSERT_EQ(a.contains("Hello"), true);
}

TEST(MultisetTest, Lower_bound) {
  s21::Multiset<int> a = {2, 45, 98, -134, -234, 1034342, -234, 234, 2, 3, 3};
  s21::Multiset<int>::iterator it = a.lower_bound(97);
  ASSERT_EQ(*it, 98);
}

TEST(MultisetTest, Upper_bound) {
  s21::Multiset<int> a = {2, 45, 98, -134, -234, 1034342, -234, 234, 2, 3, 3};
  s21::Multiset<int>::iterator it = a.upper_bound(98);
  ASSERT_EQ(*it, 234);
}

TEST(MultisetTest, EqualRange) {
  s21::Multiset<int> s = {1, 3, 3, 5, 7, 9};
  auto [it1, it2] = s.equal_range(3);
  ASSERT_EQ(*it1, 3);
  ASSERT_EQ(*it2, 5);
  auto [it3, it4] = s.equal_range(6);
  ASSERT_EQ(*it3, *it4);
  auto [it5, it6] = s.equal_range(9);
  ASSERT_EQ(*it5, 9);
}

TEST(MultisetTest, InsertMany) {
  s21::Multiset<int> a;
  auto res = a.insert_many(1, 1, 2, 2, 3, 3, 4, 4, 5);
  std::vector<int> check{1, 1, 2, 2, 3, 3, 4, 4, 5};
  EXPECT_TRUE(res[0].second);
  EXPECT_TRUE(res[1].second);
  EXPECT_TRUE(res[2].second);
  EXPECT_TRUE(res[3].second);
  EXPECT_TRUE(res[4].second);
  EXPECT_TRUE(res[5].second);
  EXPECT_TRUE(res[6].second);
  EXPECT_TRUE(res[7].second);
  EXPECT_TRUE(res[8].second);
  s21::Multiset<int>::iterator it = a.begin();
  for (size_t i = 0; it != a.end(); ++i, ++it) ASSERT_EQ(*it, check[i]);
}