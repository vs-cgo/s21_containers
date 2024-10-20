#include "../s21_array.h"

#include <gtest/gtest.h>

TEST(ArrayTest, DefaultConstructor) {
  s21::Array<int, 3> a;
  EXPECT_EQ(a.size(), 3ULL);
}

TEST(ArrayTest, DefaultConstructor1) {
  s21::Array<double, 500> a;
  EXPECT_EQ(a.size(), 500ULL);
}

TEST(ArrayTest, InitializerConstructor) {
  s21::Array<int, 5> a{1, 2, 3, 4, 5};
  std::array<int, 5> b{1, 2, 3, 4, 5};
  for (size_t i = 0; i < a.size(); ++i) EXPECT_EQ(a[i], b[i]);
  EXPECT_EQ(a.size(), 5ULL);
}

TEST(ArrayTest, InitializerConstructor1) {
  s21::Array<char, 5> a{'1', '2', '3', '4', '5'};
  std::array<char, 5> b{'1', '2', '3', '4', '5'};
  for (size_t i = 0; i < a.size(); ++i) EXPECT_EQ(a[i], b[i]);
  EXPECT_EQ(a.size(), 5ULL);
}

TEST(ArrayTest, CopyConstructor) {
  s21::Array<char, 5> a{'1', '2', '3', '4', '5'};
  std::array<char, 5> b{'1', '2', '3', '4', '5'};
  s21::Array<char, 5> c(a);
  for (size_t i = 0; i < c.size(); ++i) EXPECT_EQ(c[i], b[i]);
  EXPECT_EQ(a.size(), 5ULL);
}

TEST(ArrayTest, Move) {
  s21::Array<int, 5> int_arr1 = {1, 2, 3, 4, 5};
  s21::Array<int, 5> int_arr2 = {6, 7, 8, 9, 10};
  int_arr1 = std::move(int_arr2);
  EXPECT_EQ(int_arr1[0], 6);
  EXPECT_EQ(int_arr1[4], 10);
}

TEST(ArrayTest, EQ) {
  s21::Array<int, 5> int_arr1 = {1, 2, 3, 4, 5};
  s21::Array<int, 5> int_arr2 = int_arr1;
  s21::Array<int, 5> int_arr3 = {12, 2342, 234242, 12313, -21};
  int_arr3 = int_arr2;
  EXPECT_EQ(int_arr3[0], 1);
  EXPECT_EQ(int_arr3[4], 5);
  EXPECT_EQ(int_arr2[0], 1);
  EXPECT_EQ(int_arr2[4], 5);
}

TEST(ArrayTest, Move1) {
  s21::Array<int, 5> int_arr1 = {1, 2, 3, 4, 5};
  s21::Array<int, 5> int_arr2(std::move(int_arr1));
  EXPECT_EQ(int_arr1.size(), 0ULL);
  EXPECT_EQ(int_arr2[0], 1);
  EXPECT_EQ(int_arr2[4], 5);
}

TEST(ArrayTest, At) {
  s21::Array<double, 5> d = {2324.2342, 234.23, -1234.23, 4.23, 5.3443};
  EXPECT_EQ(d.at(3), 4.23);
  EXPECT_EQ(d.at(0), 2324.2342);
}

TEST(ArrayTest, Br) {
  s21::Array<double, 5> d = {2324.2342, 234.23, -1234.23, 4.23, 5.3443};
  EXPECT_EQ(d[3], 4.23);
  EXPECT_EQ(d[0], 2324.2342);
}

TEST(ArrayTest, Front) {
  s21::Array<std::string, 3> s = {"Hello", "st", "sdfa"};
  EXPECT_EQ(s.front(), "Hello");
}

TEST(ArrayTest, Back) {
  s21::Array<std::string, 3> s = {"Hello", "st", "sdfa"};
  EXPECT_EQ(s.back(), "sdfa");
}

TEST(ArrayTest, Data) {
  s21::Array<std::string, 3> s = {"Hello", "st", "sdfa"};
  EXPECT_EQ(*(s.data()), "Hello");
}

TEST(ArrayTest, Begin) {
  s21::Array<float, 3> s = {3.43, -134.342, -134.234};
  ASSERT_FLOAT_EQ(*(s.begin()), 3.43);
}

TEST(ArrayTest, End) {
  s21::Array<float, 3> s = {3.43, -134.342, -134.234};
  ASSERT_FLOAT_EQ(*(s.end() - 1), -134.234);
}

TEST(ArrayTest, Empty) {
  s21::Array<int, 5> arr;
  EXPECT_FALSE(arr.empty());
  s21::Array<int, 0> arr1;
  EXPECT_TRUE(arr1.empty());
}

TEST(ArrayTest, MaxSize) {
  s21::Array<int, 5> arr;
  std::array<int, 5> a;
  EXPECT_EQ(arr.max_size(), a.max_size());
}

TEST(ArrayTest, Swap) {
  s21::Array<int, 4> arr = {234, 234, 1390, 12340};
  s21::Array<int, 4> arr1 = {1, 2, 3, 4};
  arr.swap(arr1);
  ASSERT_EQ(arr1[0], 234);
  ASSERT_EQ(arr[0], 1);
  ASSERT_EQ(arr1[3], 12340);
  ASSERT_EQ(arr[3], 4);
}

TEST(ArrayTest, Fill) {
  s21::Array<int, 4> arr = {234, 234, 1390, 12340};
  arr.fill(78);
  for (size_t i = 0; i < 4; ++i) EXPECT_EQ(arr[i], 78);
}
