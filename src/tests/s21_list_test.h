#ifndef _S21_CONTAINERS_TESTS_S21_LIST_TEST_H_
#define _S21_CONTAINERS_TESTS_S21_LIST_TEST_H_

#include <gtest/gtest.h>

#include <cstring>
#include <iostream>
#include <limits>
#include <list>
#include <typeinfo>

#include "../s21_list.h"

class S21ListTest : public testing::Test {
 protected:
  S21ListTest()
      : std_l(),
        std_l1(100),
        std_l2{1, 2, 3, 4, 5, 6, 7, 8, 9, 22},
        s21_l(),
        s21_l1(100),
        s21_l2{1, 2, 3, 4, 5, 6, 7, 8, 9, 22},
        std_d(),
        std_d1(50),
        std_d2{1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 11.11},
        s21_d(),
        s21_d1(50),
        s21_d2{1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 11.11},
        std_ld(),
        std_ld1(10),
        s21_ld(),
        s21_ld1(10),
        std_c(),
        std_c1(100),
        std_c2{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'},
        s21_c(),
        s21_c1(100),
        s21_c2{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'} {}
  ~S21ListTest() {}
  // void TearDown() override {}
  void SetUp() override {}
  std::list<int> std_l, std_l1, std_l2;
  s21::list<int> s21_l, s21_l1, s21_l2;
  std::list<double> std_d, std_d1, std_d2;
  s21::list<double> s21_d, s21_d1, s21_d2;
  std::list<long double> std_ld, std_ld1;
  s21::list<long double> s21_ld, s21_ld1;
  std::list<char> std_c, std_c1, std_c2;
  s21::list<char> s21_c, s21_c1, s21_c2;
};
#endif  //_S21_CONTAINERS_TESTS_S21_LIST_TEST_H_
