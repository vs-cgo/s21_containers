#include "../s21_set.h"

#include <gtest/gtest.h>

TEST(SetTest, DefaultConstructor) {
  s21::Set<int> a;
  ASSERT_TRUE(a.empty());
}

TEST(SetTest, InitializerConstructor) {
  s21::Set<int> a{-234, -34, -1, -1, -1, 5, 6, 9};
  s21::Set<int>::iterator it = a.begin();
  std::vector<int> b{-234, -34, -1, 5, 6, 9};
  size_t i = 0;
  for (; it != a.end(); ++it) ASSERT_EQ(*it, b[i++]);

  s21::Set<std::string> a2({"abc", "deg"});
  EXPECT_EQ(a2.size(), 2ULL);
}

TEST(SetTest, CopyConstructor) {
  s21::Set<char> a{'a', 'b', 'c', 'd'};
  s21::Set<char> b(a);
  ASSERT_EQ(a.size(), b.size());
}

TEST(SetTest, MoveConstructor) {
  s21::Set<double> a{1.234, 2.234, 3.1234, 5.234, 5.89, 6.789};
  s21::Set<double> b(std::move(a));
  ASSERT_TRUE(a.empty());
  ASSERT_EQ(b.size(), 6ULL);
}

TEST(SetTest, Destructor) {
  s21::Set<int>* a = new s21::Set<int>{1, 2, 3};
  ASSERT_EQ(a->size(), 3ULL);
  delete a;
  SUCCEED();
}

TEST(SetTest, Move) {
  s21::Set<int> s1;
  s1.insert(1);
  s1.insert(2);
  s1.insert(3);
  s21::Set<int> s2;
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

TEST(SetTest, Swap) {
  s21::Set<int> a = {1, 2, 3};
  s21::Set<int> b = {4, 5, 6, 7};
  b.swap(a);
  std::vector<int> c = {1, 2, 3};
  s21::Set<int>::iterator it = b.begin();
  size_t i = 0;
  for (; it != b.end(); ++it) ASSERT_EQ(*it, c[i++]);
}

TEST(SetTest, Merge) {
  s21::Set<int> a = {10, 40, 55};
  s21::Set<int> b = {20, 40, 66};
  std::vector<int> c = {10, 20, 40, 55, 66};
  a.merge(b);
  EXPECT_FALSE(b.empty());
  s21::Set<int>::iterator it = a.begin();
  size_t i = 0;
  for (; it != a.end(); ++it, ++i) ASSERT_EQ(*it, c[i]);
}

TEST(SetTest, Find) {
  s21::Set<std::string> s;
  auto iter = s.find("one");
  ASSERT_EQ(iter.get(), s.end().get());
}

TEST(SetTest, Size) {
  s21::Set<float> a;
  a.insert(23.234);
  a.insert(13.234);
  a.insert(33.89);
  EXPECT_EQ(a.size(), 3ULL);
}

TEST(SetTest, MaxSize) {
  s21::Set<float> a;
  std::set<float> b;
  s21::Set<std::string> c;
  std::set<std::string> d;
  EXPECT_EQ(a.max_size(), b.max_size());
}

TEST(SetTest, Clear) {
  s21::Set<int> s;
  s.insert(1);
  s.insert(2);
  s.insert(3);
  EXPECT_EQ(s.size(), 3ULL);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
  s.clear();
  EXPECT_EQ(s.size(), 0ULL);
  EXPECT_FALSE(s.contains(1));
  EXPECT_FALSE(s.contains(2));
  EXPECT_FALSE(s.contains(3));
}

TEST(SetTest, Insert) {
  s21::Set<int> set;
  set.insert(34);
  set.insert(112);
  set.insert(67);
  EXPECT_EQ(set.size(), 3ULL);
  EXPECT_TRUE(set.contains(34));
  EXPECT_TRUE(set.contains(112));
  EXPECT_TRUE(set.contains(67));
  EXPECT_FALSE(set.insert(67).second);
  EXPECT_TRUE(set.insert(78).second);
}

TEST(SetTest, InsertString) {
  s21::Set<std::string> s;
  s.insert("foo");
  s.insert("Hi");
  s.insert("4ert");
  EXPECT_TRUE(s.contains("foo"));
  EXPECT_TRUE(s.contains("Hi"));
  EXPECT_TRUE(s.contains("4ert"));
  EXPECT_FALSE(s.insert("foo").second);
}

TEST(SetTest, Erase) {
  s21::Set<int> a{1, 2, 3, 4, 5, 6, 7, 8};
  std::vector<int> b{1, 2, 4, 5, 7};
  auto it1 = a.find(3);
  a.erase(it1);
  auto it2 = a.find(8);
  a.erase(it2);
  auto it3 = a.find(6);
  a.erase(it3);
  auto it4 = a.begin();
  size_t i = 0;
  for (; it4 != a.end(); ++it4, ++i) ASSERT_EQ(*it4, b[i]);
  ASSERT_EQ(a.size(), 5ULL);
}

TEST(SetTest, InsertMany) {
  s21::Set<std::string> a;
  auto res = a.insert_many("123", "345", "678");
  EXPECT_TRUE(res[0].second);
  EXPECT_TRUE(res[1].second);
  EXPECT_TRUE(res[2].second);
  auto res1 = a.insert_many("123", "345", "678");
  EXPECT_FALSE(res1[0].second);
  EXPECT_FALSE(res1[1].second);
  EXPECT_FALSE(res1[2].second);
}