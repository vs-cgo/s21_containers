#include "../s21_vector.h"

#include <gtest/gtest.h>

class S21VectorTest : public ::testing::Test {
 protected:
  s21::Vector<int> int_v = {0, 1, 2, 3, 4, 5};
  s21::Vector<double> double_v = {0.1, 1.1, 2.2, 3.3, 4.4, 5.5};
  s21::Vector<char> char_v = {'a', 'b', 'c', 'D'};
  s21::Vector<int> const const_int_v = {0, 1, 2, 3, 4};
  s21::Vector<float> zero_v;

  std::vector<int> std_int_v = {0, 1, 2, 3, 4, 5};
  std::vector<double> std_double_v = {0.1, 1.1, 2.2, 3.3, 4.4, 5.5};
  std::vector<char> std_char_v = {'a', 'b', 'c', 'D'};
  std::vector<int> const std_const_int_v = {0, 1, 2, 3, 4};
  std::vector<float> std_zero_v;
};

TEST_F(S21VectorTest, DefCon) {
  EXPECT_EQ(zero_v.size(), std_zero_v.size());
  EXPECT_EQ(zero_v.capacity(), std_zero_v.capacity());
  EXPECT_EQ(zero_v.data(), nullptr);
  EXPECT_EQ(std_zero_v.data(), nullptr);
}

TEST_F(S21VectorTest, PushBack) {
  zero_v.push_back(3);
  std_zero_v.push_back(3);
  EXPECT_EQ(zero_v.front(), std_zero_v.front());
}

TEST_F(S21VectorTest, MaxSize) {
  EXPECT_EQ(double_v.max_size(), std_double_v.max_size());
  EXPECT_EQ(int_v.max_size(), std_int_v.max_size());
  EXPECT_EQ(char_v.max_size(), std_char_v.max_size());
}

TEST(VectorTest, MaxSize1) {
  s21::Vector<std::string> a;
  std::vector<std::string> b;
  EXPECT_EQ(a.max_size(), b.max_size());
}

TEST_F(S21VectorTest, ConstCon) {
  s21::Vector<int> a(const_int_v);
  std::vector<int> b(std_const_int_v);
  for (size_t i = 0; i < a.size(); i++) {
    EXPECT_EQ(*(a.data() + i), *(b.data() + i));
  }
}

TEST_F(S21VectorTest, MoveConAndData) {
  s21::Vector<int> a(std::move(int_v));
  std::vector<int> b(std::move(std_int_v));
  for (size_t i = 0; i < a.size(); i++) {
    EXPECT_EQ(*(a.data() + i), *(b.data() + i));
  }
}

TEST_F(S21VectorTest, At) {
  EXPECT_EQ(char_v.at(2), std_char_v.at(2));
  EXPECT_EQ(double_v.at(3), std_double_v.at(3));
  EXPECT_EQ(int_v.at(0), std_int_v.at(0));
}

TEST_F(S21VectorTest, Eq) {
  s21::Vector<int> a = {23, 56, 78};
  s21::Vector<int> b = a;
  std::vector<int> std_a = {23, 56, 78};
  std::vector<int> std_b = std_a;
  EXPECT_EQ(b[1], std_b[1]);
}

TEST_F(S21VectorTest, Front) {
  EXPECT_EQ(double_v.front(), std_double_v.front());
}

TEST_F(S21VectorTest, Back) { EXPECT_EQ(double_v.back(), std_double_v.back()); }

TEST_F(S21VectorTest, Begin) {
  EXPECT_EQ(*char_v.begin(), *std_char_v.begin());
}

TEST_F(S21VectorTest, End) { EXPECT_EQ(*char_v.end(), *std_char_v.end()); }

TEST_F(S21VectorTest, Empty) {
  ASSERT_TRUE(zero_v.empty());
  ASSERT_FALSE(char_v.empty());
}

TEST_F(S21VectorTest, Size) {
  EXPECT_EQ(char_v.size(), std_char_v.size());
  EXPECT_EQ(double_v.size(), std_double_v.size());
  EXPECT_EQ(int_v.size(), std_int_v.size());
}

TEST_F(S21VectorTest, Reserve) {
  char_v.reserve(10);
  std_char_v.reserve(10);
  EXPECT_EQ(char_v.size(), std_char_v.size());
  EXPECT_EQ(char_v.capacity(), std_char_v.capacity());
}

TEST_F(S21VectorTest, ShrinkToFit) {
  char_v.reserve(30);
  std_char_v.reserve(30);
  char_v.shrink_to_fit();
  std_char_v.shrink_to_fit();
  EXPECT_EQ(char_v.size(), std_char_v.size());
  EXPECT_EQ(char_v.capacity(), std_char_v.capacity());
}

TEST_F(S21VectorTest, Clear) {
  int_v.clear();
  std_int_v.clear();
  EXPECT_EQ(char_v.size(), std_char_v.size());
  EXPECT_EQ(char_v.capacity(), std_char_v.capacity());
}

TEST_F(S21VectorTest, Insert) {
  double_v.insert((double_v.data() + 3), 5.5);
  EXPECT_EQ(double_v[3], 5.5);
}

TEST_F(S21VectorTest, Iter) {
  // s21::Vector<int> int_v = {0, 1, 2, 3, 4, 5};
  // s21::Vector<double> double_v = {0.1, 1.1, 2.2, 3.3, 4.4, 5.5};
  s21::Vector<double>::iterator a = double_v.data();
  s21::Vector<int>::iterator b = int_v.end();
  EXPECT_EQ(*a, *double_v.data());
  EXPECT_EQ(*b, *int_v.end());
}

TEST_F(S21VectorTest, Erase) {
  // {0.1, 1.1, 2.2, 3.3, 4.4, 5.5}
  double_v.erase((double_v.data() + 3));
  // {0.1, 1.2, 2.2, 4.4, 5.5}
  EXPECT_EQ(double_v[3], 4.4);
}

TEST_F(S21VectorTest, PopBack) {
  int_v.pop_back();
  std_int_v.pop_back();
  EXPECT_EQ(int_v.back(), std_int_v.back());
}

TEST_F(S21VectorTest, Swap) {
  s21::Vector<int> a({100, 200, 300, 400, 500});
  // int_v({0, 1, 2, 3, 4, 5});
  a.swap(int_v);
  EXPECT_EQ(a[1], 1);
  EXPECT_EQ(int_v[1], 200);
}

TEST(VectorTest, InsertMany) {
  s21::Vector<int> a{1, 2, 45};
  a.insert_many((a.begin() + 1), 3, 4, 5, 8, 9);
  s21::Vector<int> b{1, 3, 4, 5, 8, 9, 2, 45};
  for (size_t i = 0; i < a.size(); ++i) EXPECT_EQ(a[i], b[i]);
}

TEST(VectorTest, InsertManyBack) {
  s21::Vector<int> a{1, 2};
  a.insert_many_back(3, 4, 5, 8, 9);
  s21::Vector<int> b{1, 2, 3, 4, 5, 8, 9};
  s21::Vector<int>::iterator c = a.begin() + 7;
  for (size_t i = 0; i < a.size(); ++i) EXPECT_EQ(a[i], b[i]);
  EXPECT_EQ(*c, *a.end());
}
