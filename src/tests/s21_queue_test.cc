#include "../s21_queue.h"

#include <gtest/gtest.h>

TEST(TestQueue, DefaultConstructor) {
  s21::Queue<int> a;
  EXPECT_TRUE(a.empty());
}

TEST(TestQueue, InitializerConstructor) {
  s21::Queue<int> a({1234, 1234, 234, 2134, 123});
  EXPECT_EQ(a.size(), 5ULL);
  EXPECT_EQ(a.front(), 1234);
  EXPECT_EQ(a.back(), 123);
}

TEST(TestQueue, CopyConstructor) {
  s21::Queue<int> a({1234, 1234, 234, 2134, 123});
  s21::Queue<int> b(a);
  EXPECT_EQ(b.front(), 1234);
  EXPECT_EQ(b.back(), 123);
}

TEST(TestQueue, MoveConstructor) {
  s21::Queue<int> a({1234, 1234, 234, 2134, 123});
  s21::Queue<int> b(std::move(a));
  EXPECT_EQ(b.size(), 5ULL);
  EXPECT_EQ(a.size(), 0ULL);
  EXPECT_EQ(b.front(), 1234);
  EXPECT_EQ(b.back(), 123);
}

TEST(TestQueue, Push) {
  s21::Queue<int> a;
  a.push(123);
  a.push(2456);
  a.push(-123);
  EXPECT_EQ(a.size(), 3ULL);
  EXPECT_EQ(a.front(), 123);
  EXPECT_EQ(a.back(), -123);
}

TEST(TestQueue, Pop) {
  s21::Queue<int> a;
  a.push(123);
  a.push(2456);
  a.push(-123);
  a.pop();
  EXPECT_EQ(a.size(), 2ULL);
  EXPECT_EQ(a.front(), 2456);
  EXPECT_EQ(a.back(), -123);
}

TEST(TestQueue, Swap) {
  s21::Queue<char> a({'a', '3', 'g'});
  s21::Queue<char> b({'b', '2', 'c'});
  a.swap(b);
  EXPECT_EQ(a.size(), 3ULL);
  EXPECT_EQ(a.front(), 'b');
  EXPECT_EQ(a.back(), 'c');
}

TEST(TestQueue, InsertManyBack) {
  s21::Queue<char> a({'a', '3', 'g'});
  a.insert_many_back('e', 'r', 'i');
  EXPECT_EQ(a.size(), 6ULL);
  EXPECT_EQ(a.front(), 'a');
  EXPECT_EQ(a.back(), 'i');
}