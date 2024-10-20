#include "../s21_stack.h"

#include <gtest/gtest.h>

#include <stack>

TEST(StackTest, Default_Constructor) {
  s21::Stack<int> a;
  std::stack<int> b;
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.empty(), b.empty());
}

TEST(StackTest, InitializerConstructor) {
  s21::Stack<int> s1{1, 2, 3, 4};
  ASSERT_EQ(s1.size(), 4ULL);
  ASSERT_EQ(s1.top(), 4);
  s21::Stack<std::string> s2{"Hello", "$ert", "Vector-g"};
  ASSERT_EQ(s2.size(), 3ULL);
  ASSERT_EQ(s2.top(), "Vector-g");
}

TEST(StackTest, CopyConstructor) {
  s21::Stack<int> s1{1, 2, 3, 4};
  s21::Stack<int> s2(s1);
  ASSERT_EQ(s2.size(), 4ULL);
  ASSERT_EQ(s2.top(), 4);
}

TEST(StackTest, MoveConstructor) {
  s21::Stack<int> s1{1, 2, 3, 4};
  s21::Stack<int> s2(std::move(s1));
  ASSERT_EQ(s1.size(), 0ULL);
  ASSERT_EQ(s2.size(), 4ULL);
  ASSERT_EQ(s2.top(), 4);
}

TEST(StackTest, Eq) {
  s21::Stack<int> s1{1, 2, 3, 4};
  s21::Stack<int> s2 = (std::move(s1));
  ASSERT_EQ(s1.size(), 0ULL);
  ASSERT_EQ(s2.size(), 4ULL);
  ASSERT_EQ(s2.top(), 4);
}

TEST(StackTest, Eq1) {
  s21::Stack<int> s1{1, 2, 3, 4};
  s21::Stack<int> s2 = s1;
  ASSERT_EQ(s1.size(), 4ULL);
  ASSERT_EQ(s2.size(), 4ULL);
  ASSERT_EQ(s1.top(), 4);
  ASSERT_EQ(s2.top(), 4);
}

TEST(StackTest, Push) {
  s21::Stack<int> s1{1, 2, 3, 4};
  s1.push(6);
  ASSERT_EQ(s1.size(), 5ULL);
  ASSERT_EQ(s1.top(), 6);
}

TEST(StackTest, Pop) {
  s21::Stack<int> s1{1, 2, 3, 4};
  s1.push(6);
  s1.pop();
  ASSERT_EQ(s1.size(), 4ULL);
  ASSERT_EQ(s1.top(), 4);
}

TEST(StackTest, Swap) {
  s21::Stack<int> s1{1, 2, 3, 4};
  s21::Stack<int> s2{5, 6, 7, 8};
  s1.swap(s2);
  ASSERT_EQ(s1.top(), 8);
  ASSERT_EQ(s2.top(), 4);
}

TEST(StackTest, InsertManyFront) {
  s21::Stack<int> a{1, 2};
  a.insert_many_front(3, 4, 5, 8, 9);
  a.pop();
  a.pop();
  ASSERT_EQ(a.size(), 5ULL);
  ASSERT_EQ(a.top(), 3);
}
