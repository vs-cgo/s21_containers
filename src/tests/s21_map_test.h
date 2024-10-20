#ifndef _S21_CONTAINERS_TESTS_S21_MAP_TEST_H_
#define _S21_CONTAINERS_TESTS_S21_MAP_TEST_H_

#include <gtest/gtest.h>

#include <cstring>
#include <iostream>
#include <limits>
#include <map>
#include <typeinfo>

#include "../s21_map.h"

class S21MapTest : public testing::Test {
 protected:
  S21MapTest()
      : s21_ic{{1, 'A'}, {2, 'B'}, {3, 'C'}, {4, 'D'},
               {5, 'E'}, {6, 'F'}, {7, 'G'}, {8, 'H'}},
        s21_ic_empty(),
        std_ic{{1, 'A'}, {2, 'B'}, {3, 'C'}, {4, 'D'},
               {5, 'E'}, {6, 'F'}, {7, 'G'}, {8, 'H'}},
        std_ic_empty(),
        s21_ii{{15, 65}, {18, 66}, {17, 67}, {14, 68},
               {20, 69}, {19, 70}, {13, 71}, {12, 72}},
        s21_ii_empty(),
        std_ii{{15, 65}, {18, 66}, {17, 67}, {14, 68},
               {20, 69}, {19, 70}, {13, 71}, {12, 72}},
        std_ii_empty(),
        s21_si{{"Lemon", 10},  {"Pear", 11},   {"Mango", 12}, {"Apple", 13},
               {"Banana", 14}, {"Orange", 15}, {"Grape", 16}, {"Coconut", 17},
               {"Kiwi", 18},   {"Fig", 19}},
        s21_si_empty(),
        std_si{{"Lemon", 10},  {"Pear", 11},   {"Mango", 12}, {"Apple", 13},
               {"Banana", 14}, {"Orange", 15}, {"Grape", 16}, {"Coconut", 17},
               {"Kiwi", 18},   {"Fig", 19}},
        std_si_empty(),
        s21_is{{9, "Strawberry"}, {1, "Blueberry"}, {8, "Cranberry"},
               {2, "Currant"},    {7, "Bilberry"},  {3, "Cherry"},
               {6, "Plum"},       {4, "Melon"},     {5, "Watermelon"}},
        s21_is_empty(),
        std_is{{9, "Strawberry"}, {1, "Blueberry"}, {8, "Cranberry"},
               {2, "Currant"},    {7, "Bilberry"},  {3, "Cherry"},
               {6, "Plum"},       {4, "Melon"},     {5, "Watermelon"}},
        std_is_empty(),
        s21_ss{{"one", "test"}, {"two", "omnomnom"}},
        std_ss{{"one", "test"}, {"two", "omnomnom"}},

        s21_ic_it(),
        s21_ic_end(),
        std_ic_it(),
        std_ic_end(),
        s21_ii_it(),
        s21_ii_end(),
        std_ii_it(),
        std_ii_end(),
        s21_si_it(),
        s21_si_end(),
        std_si_it(),
        std_si_end(),
        s21_is_it(),
        s21_is_end(),
        std_is_it(),
        std_is_end(),
        s21_ss_it(),
        std_ss_it(){};
  ~S21MapTest(){};
  // void TearDown() override {}
  void SetUp() override {}
  s21::map<int, char> s21_ic, s21_ic_empty;
  std::map<int, char> std_ic, std_ic_empty;
  s21::map<int, int> s21_ii, s21_ii_empty;
  std::map<int, int> std_ii, std_ii_empty;
  s21::map<std::string, int> s21_si, s21_si_empty;
  std::map<std::string, int> std_si, std_si_empty;
  s21::map<int, std::string> s21_is, s21_is_empty;
  std::map<int, std::string> std_is, std_is_empty;
  s21::map<std::string, std::string> s21_ss;
  std::map<std::string, std::string> std_ss;

  s21::map<int, char>::iterator s21_ic_it, s21_ic_end;
  std::map<int, char>::iterator std_ic_it, std_ic_end;
  s21::map<int, int>::iterator s21_ii_it, s21_ii_end;
  std::map<int, int>::iterator std_ii_it, std_ii_end;
  s21::map<std::string, int>::iterator s21_si_it, s21_si_end;
  std::map<std::string, int>::iterator std_si_it, std_si_end;
  s21::map<int, std::string>::iterator s21_is_it, s21_is_end;
  std::map<int, std::string>::iterator std_is_it, std_is_end;
  s21::map<std::string, std::string>::iterator s21_ss_it;
  std::map<std::string, std::string>::iterator std_ss_it;
  void print(std::map<int, int>::iterator t, s21::map<int, int>::iterator s) {
    std::cout << '[' << t->first << "] = " << t->second << " : " << '['
              << s->first << "]=" << s->second << '\n';
  };
  void print(std::map<int, char>::iterator t, s21::map<int, char>::iterator s) {
    std::cout << '[' << t->first << "] = " << t->second << " : " << '['
              << s->first << "]=" << s->second << '\n';
  };
  void print(std::map<std::string, int>::iterator t,
             s21::map<std::string, int>::iterator s) {
    std::cout << '[' << t->first << "] = " << t->second << " : " << '['
              << s->first << "]=" << s->second << '\n';
  };
  void print(std::map<int, std::string>::iterator t,
             s21::map<int, std::string>::iterator s) {
    std::cout << '[' << t->first << "] = " << t->second << " : " << '['
              << s->first << "]=" << s->second << '\n';
  };
  void print(
      std::map<std::string, int, std::greater<std::string>>::iterator t,
      s21::map<std::string, int, std::greater<std::string>>::iterator s) {
    std::cout << '[' << t->first << "] = " << t->second << " : " << '['
              << s->first << "]=" << s->second << '\n';
  };
};
#endif  //_S21_CONTAINERS_TESTS_S21_MAP_TEST_H_
