#include "s21_map_test.h"

#include <cstdlib>
#include <ctime>

TEST_F(S21MapTest, ConstructorDefault) {
  EXPECT_EQ(std_ii_empty.size(), s21_ii_empty.size());
  EXPECT_EQ(std_si_empty.size(), s21_si_empty.size());
  EXPECT_EQ(std_is_empty.size(), s21_ii_empty.size());
}

TEST_F(S21MapTest, ConstructionInitializer) {
  s21_ic_it = s21_ic.begin();
  std_ic_it = std_ic.begin();
  for (int i = 0; i < 10; ++i, ++s21_ic_it, ++std_ic_it) {
    EXPECT_EQ(std_ic_it->first, s21_ic_it->first);
    EXPECT_EQ(std_ic_it->second, s21_ic_it->second);
    // print(std_ic_it, s21_ic_it);
  }

  s21_ii_it = s21_ii.begin();
  std_ii_it = std_ii.begin();
  for (int i = 0; i < 10; ++i, ++s21_ii_it, ++std_ii_it) {
    EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
    EXPECT_EQ(std_ii_it->second, s21_ii_it->second);
    // print(std_ii_it, s21_ii_it);
  }

  s21_si_it = s21_si.begin();
  std_si_it = std_si.begin();
  for (int i = 0; i < 10; ++i, ++s21_si_it, ++std_si_it) {
    EXPECT_EQ(std_si_it->first, s21_si_it->first);
    EXPECT_EQ(std_si_it->second, s21_si_it->second);
    // print(std_si_it, s21_si_it);
  }
  s21_is_it = s21_is.begin();
  std_is_it = std_is.begin();
  for (int i = 0; i < 9; ++i, ++s21_is_it, ++std_is_it) {
    EXPECT_EQ(std_is_it->first, s21_is_it->first);
    EXPECT_EQ(std_is_it->second, s21_is_it->second);
    // print(std_is_it, s21_is_it);
  }
}

TEST_F(S21MapTest, ConstructorCopy) {
  {
    s21::map<int, int> copy_s(s21_ii);
    std::map<int, int> copy_t = std_ii;

    s21_ii_it = copy_s.begin();
    std_ii_it = copy_t.begin();
    std_ii_end = copy_t.end();

    EXPECT_EQ(8, copy_t.size());
    EXPECT_EQ(8, copy_s.size());

    for (; std_ii_it != std_ii_end; ++s21_ii_it, ++std_ii_it) {
      EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
      EXPECT_EQ(std_ii_it->second, s21_ii_it->second);
      // print(std_ii_it, s21_ii_it);
    }
  }
  {
    s21::map<int, std::string> copy_s(s21_is);
    std::map<int, std::string> copy_t = std_is;

    s21_is_it = copy_s.begin();
    std_is_it = copy_t.begin();
    std_is_end = copy_t.end();

    EXPECT_EQ(9, copy_t.size());
    EXPECT_EQ(9, copy_s.size());

    for (; std_is_it != std_is_end; ++s21_is_it, ++std_is_it) {
      EXPECT_EQ(std_is_it->first, s21_is_it->first);
      EXPECT_EQ(std_is_it->second, s21_is_it->second);
      // print(std_is_it, s21_is_it);
    }
  }
}

TEST_F(S21MapTest, ConstructorMove) {
  {
    s21::map<int, int> move_s(std::move(s21_ii));
    std::map<int, int> move_t = (std::move(std_ii));

    s21_ii_it = move_s.begin();
    std_ii_it = move_t.begin();
    std_ii_end = move_t.end();

    EXPECT_EQ(0, s21_ii.size());
    EXPECT_EQ(0, std_ii.size());
    EXPECT_EQ(8, move_s.size());
    EXPECT_EQ(8, move_t.size());
    for (; std_ii_it != std_ii_end; ++s21_ii_it, ++std_ii_it) {
      EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
      EXPECT_EQ(std_ii_it->second, s21_ii_it->second);
      // print(std_ii_it, s21_ii_it);
    }
  }
  {
    s21::map<int, std::string> move_s(std::move(s21_is));
    std::map<int, std::string> move_t = (std::move(std_is));

    s21_is_it = move_s.begin();
    std_is_it = move_t.begin();
    std_is_end = move_t.end();

    EXPECT_EQ(0, s21_is.size());
    EXPECT_EQ(0, std_is.size());
    EXPECT_EQ(9, move_s.size());
    EXPECT_EQ(9, move_t.size());

    for (; std_is_it != std_is_end; ++s21_is_it, ++std_is_it) {
      EXPECT_EQ(std_is_it->first, s21_is_it->first);
      EXPECT_EQ(std_is_it->second, s21_is_it->second);
      // print(std_is_it, s21_is_it);
    }
  }
}
TEST_F(S21MapTest, OperatorAssignmentCopy) {
  std_ii_empty = std_ii;
  s21_ii_empty = s21_ii;
  s21_ii_it = s21_ii_empty.begin();
  std_ii_it = std_ii_empty.begin();
  std_ii_end = std_ii_empty.end();

  EXPECT_EQ(std_ii.size(), s21_ii.size());
  EXPECT_EQ(std_ii_empty.size(), s21_ii_empty.size());

  for (; std_ii_it != std_ii_end; ++s21_ii_it, ++std_ii_it) {
    EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
    EXPECT_EQ(std_ii_it->second, s21_ii_it->second);
    // print(std_ii_it, s21_ii_it);
  }

  std::map<int, int> t = {{100, 1000}};
  s21::map<int, int> s = {{100, 1000}};
  t = std_ii;
  s = s21_ii;
  s21_ii_it = s.begin();
  std_ii_it = t.begin();
  std_ii_end = t.end();

  EXPECT_EQ(t.size(), s.size());
  EXPECT_EQ(std_ii.size(), s21_ii.size());

  for (; std_ii_it != std_ii_end; ++s21_ii_it, ++std_ii_it) {
    EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
    EXPECT_EQ(std_ii_it->second, s21_ii_it->second);
    // print(std_ii_it, s21_ii_it);
  }

  std_si_empty = std_si;
  s21_si_empty = s21_si;
  s21_si_it = s21_si_empty.begin();
  std_si_it = std_si_empty.begin();
  std_si_end = std_si_empty.end();

  EXPECT_EQ(std_si.size(), s21_si.size());
  EXPECT_EQ(std_si_empty.size(), s21_si_empty.size());

  for (; std_si_it != std_si_end; ++s21_si_it, ++std_si_it) {
    EXPECT_EQ(std_si_it->first, s21_si_it->first);
    EXPECT_EQ(std_si_it->second, s21_si_it->second);
    // print(std_si_it, s21_si_it);
  }
}

TEST_F(S21MapTest, OperatorAssignmentMove) {
  std_ii_empty = std::move(std_ii);
  s21_ii_empty = std::move(s21_ii);
  s21_ii_it = s21_ii_empty.begin();
  std_ii_it = std_ii_empty.begin();
  std_ii_end = std_ii_empty.end();

  EXPECT_EQ(std_ii.size(), s21_ii.size());
  EXPECT_EQ(std_ii_empty.size(), s21_ii_empty.size());

  for (; std_ii_it != std_ii_end; ++s21_ii_it, ++std_ii_it) {
    EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
    EXPECT_EQ(std_ii_it->second, s21_ii_it->second);
    // print(std_ii_it, s21_ii_it);
  }

  std_si_empty = std::move(std_si);
  s21_si_empty = std::move(s21_si);
  s21_si_it = s21_si_empty.begin();
  std_si_it = std_si_empty.begin();
  std_si_end = std_si_empty.end();

  EXPECT_EQ(std_si.size(), s21_si.size());
  EXPECT_EQ(std_si_empty.size(), s21_si_empty.size());

  for (; std_si_it != std_si_end; ++s21_si_it, ++std_si_it) {
    EXPECT_EQ(std_si_it->first, s21_si_it->first);
    EXPECT_EQ(std_si_it->second, s21_si_it->second);
    // print(std_si_it, s21_si_it);
  }
}

TEST_F(S21MapTest, At) {
  EXPECT_EQ(std_ic.at(6), s21_ic.at(6));
  EXPECT_EQ(std_ii.at(18), s21_ii.at(18));
  EXPECT_EQ(std_is.at(9), s21_is.at(9));

  std_ic.at(6) = 'Z';
  s21_ic.at(6) = 'Z';
  std_ii.at(18) = 180;
  s21_ii.at(18) = 180;
  std_is.at(9) = "Banana";
  s21_is.at(9) = "Banana";

  EXPECT_EQ(std_ic.at(6), s21_ic.at(6));
  EXPECT_EQ(std_ii.at(18), s21_ii.at(18));
  EXPECT_EQ(std_is.at(9), s21_is.at(9));

  // EXPECT_THROW(std_si.at("Kivi"), std::out_of_range);
  // EXPECT_THROW(s21_si.at("Kivi"), std::out_of_range);
}

TEST_F(S21MapTest, OperatorBracket) {
  std::srand(std::time(nullptr));
  for (int i = 0; i < 20; ++i) {
    int v = rand() % 100;
    s21_ic_empty[v] = i + 97;
    std_ic_empty[v] = i + 97;
  }

  // s21_ic_empty.print();
  s21_ic_it = s21_ic_empty.begin();
  std_ic_it = std_ic_empty.begin();
  std_ic_end = std_ic_empty.end();

  EXPECT_EQ(std_ic_empty.size(), s21_ic_empty.size());
  for (; std_ic_it != std_ic_end; ++std_ic_it, ++s21_ic_it) {
    EXPECT_EQ(std_ic_it->first, s21_ic_it->first);
    EXPECT_EQ(std_ic_it->second, s21_ic_it->second);
    // print(std_ic_it, s21_ic_it);
  }
  s21_si_empty[""] = 12345;
  std_si_empty[""] = 12345;
  s21_si_empty["test"] = 45;
  std_si_empty["test"] = 45;

  s21_si_it = s21_si_empty.begin();
  std_si_it = std_si_empty.begin();
  std_si_end = std_si_empty.end();

  EXPECT_EQ(std_si_empty.size(), s21_si_empty.size());
  for (; std_si_it != std_si_end; ++std_si_it, ++s21_si_it) {
    EXPECT_EQ(std_si_it->first, s21_si_it->first);
    EXPECT_EQ(std_si_it->second, s21_si_it->second);
    // print(std_si_it, s21_si_it);
  }
}

TEST_F(S21MapTest, Begin) {
  s21_ii_it = s21_ii.begin();
  std_ii_it = std_ii.begin();
  EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
  EXPECT_EQ(std_ii_it->second, s21_ii_it->second);
  for (int i = 0; i < 15; ++i, ++std_ii_it, ++s21_ii_it) {
    EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
    EXPECT_EQ(std_ii_it->second, s21_ii_it->second);
  }
  s21_ii_it = s21_ii.begin();
  std_ii_it = std_ii.begin();
  for (int i = 0; i < 15; ++i, std_ii_it++, s21_ii_it++) {
    EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
    EXPECT_EQ(std_ii_it->second, s21_ii_it->second);
  }
  s21_ii_it = s21_ii.begin();
  std_ii_it = std_ii.begin();
  for (int i = 0; i < 15; ++i, --std_ii_it, --s21_ii_it) {
    EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
    EXPECT_EQ(std_ii_it->second, s21_ii_it->second);
  }
  s21_ii_it = s21_ii.begin();
  std_ii_it = std_ii.begin();
  for (int i = 0; i < 15; ++i, std_ii_it--, s21_ii_it--) {
    EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
    EXPECT_EQ(std_ii_it->second, s21_ii_it->second);
  }
  // string-int;
  s21_si_it = s21_si.begin();
  std_si_it = std_si.begin();
  std_si_end = std_si.end();
  EXPECT_EQ(std_si_it->first, s21_si_it->first);
  EXPECT_EQ(std_si_it->second, s21_si_it->second);
  for (; std_si_it != std_si_end; ++std_si_it, ++s21_si_it) {
    EXPECT_EQ(std_si_it->first, s21_si_it->first);
    EXPECT_EQ(std_si_it->second, s21_si_it->second);
    // print(std_si_it, s21_si_it);
  }
  s21_si_it = s21_si.begin();
  std_si_it = std_si.begin();
  for (; std_si_it != std_si_end; std_si_it++, s21_si_it++) {
    EXPECT_EQ(std_si_it->first, s21_si_it->first);
    EXPECT_EQ(std_si_it->second, s21_si_it->second);
    // print(std_si_it, s21_si_it);
  }
  s21_si_it = --s21_si.end();
  std_si_it = --std_si.end();
  for (; std_si_it != std_si_end; --std_si_it, --s21_si_it) {
    EXPECT_EQ(std_si_it->first, s21_si_it->first);
    EXPECT_EQ(std_si_it->second, s21_si_it->second);
    // print(std_si_it, s21_si_it);
  }
  s21_si_it = --s21_si.end();
  std_si_it = --std_si.end();
  for (; std_si_it != std_si_end; std_si_it--, s21_si_it--) {
    EXPECT_EQ(std_si_it->first, s21_si_it->first);
    EXPECT_EQ(std_si_it->second, s21_si_it->second);
    // print(std_si_it, s21_si_it);
  }
}

TEST_F(S21MapTest, End) {
  s21_ic_it = --s21_ic.end();
  std_ic_it = --std_ic.end();
  s21_ii_it = --s21_ii.end();
  std_ii_it = --std_ii.end();
  s21_is_it = --s21_is.end();
  std_is_it = --std_is.end();

  EXPECT_EQ(std_ic_it->first, s21_ic_it->first);
  EXPECT_EQ(std_ic_it->second, s21_ic_it->second);
  EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
  EXPECT_EQ(std_ii_it->second, s21_ii_it->second);
  EXPECT_EQ(std_is_it->first, s21_is_it->first);
  EXPECT_EQ(std_is_it->second, s21_is_it->second);

  std_is_end = std_is.end();
  for (; std_is_it != std_is_end; std_is_it--, s21_is_it--) {
    EXPECT_EQ(std_is_it->first, s21_is_it->first);
    EXPECT_EQ(std_is_it->second, s21_is_it->second);
  }
}

TEST_F(S21MapTest, Empty) {
  EXPECT_EQ(std_ic_empty.empty(), s21_ic_empty.empty());
  EXPECT_EQ(std_ii_empty.empty(), s21_ii_empty.empty());
  EXPECT_EQ(std_si_empty.empty(), s21_si_empty.empty());
  EXPECT_EQ(std_ii.empty(), s21_ii.empty());
  EXPECT_EQ(std_is.empty(), s21_is.empty());
}

TEST_F(S21MapTest, Size) {
  EXPECT_EQ(std_ic_empty.size(), s21_ic_empty.size());
  EXPECT_EQ(std_si_empty.size(), s21_si_empty.size());
  EXPECT_EQ(std_ic.size(), s21_ic.size());
  EXPECT_EQ(std_ii.size(), s21_ii.size());
  EXPECT_EQ(std_is.size(), s21_is.size());
}

TEST_F(S21MapTest, MaxSize) {
  EXPECT_EQ(std_ic.max_size(), s21_ic.max_size());
  EXPECT_EQ(std_ii.max_size(), s21_ii.max_size());
  EXPECT_EQ(std_si.max_size(), s21_si.max_size());
  EXPECT_EQ(std_is.max_size(), s21_is.max_size());
  EXPECT_EQ(std_ss.max_size(), s21_ss.max_size());
}

TEST_F(S21MapTest, Clear) {
  std_ic.clear();
  s21_ic.clear();
  EXPECT_EQ(std_ic.size(), s21_ic.size());

  std_ii.clear();
  s21_ii.clear();
  EXPECT_EQ(std_ii.size(), s21_ii.size());

  std_si.clear();
  s21_si.clear();
  EXPECT_EQ(std_si.size(), s21_si.size());

  std_is.clear();
  s21_is.clear();
  EXPECT_EQ(std_is.size(), s21_is.size());
}

TEST_F(S21MapTest, InsertPair) {
  {
    std::pair<std::map<int, int>::iterator, bool> t;
    std::pair<s21::map<int, int>::iterator, bool> s;

    t = std_ii.insert({16, 100});
    s = s21_ii.insert({16, 100});
    std_ii_it = t.first;
    s21_ii_it = s.first;

    EXPECT_EQ(t.second, s.second);
    EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
    EXPECT_EQ(std_ii_it->second, s21_ii_it->second);

    t = std_ii.insert({16, 99});
    s = s21_ii.insert({16, 99});
    std_ii_it = t.first;
    s21_ii_it = s.first;

    EXPECT_EQ(t.second, s.second);
    EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
    EXPECT_EQ(std_ii_it->second, s21_ii_it->second);
  }
  {
    std::pair<std::map<int, int>::iterator, bool> t;
    std::pair<s21::map<int, int>::iterator, bool> s;

    t = std_ii_empty.insert({16, 100});
    s = s21_ii_empty.insert({16, 100});
    std_ii_it = t.first;
    s21_ii_it = s.first;

    EXPECT_EQ(t.second, s.second);
    EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
    EXPECT_EQ(std_ii_it->second, s21_ii_it->second);

    t = std_ii_empty.insert({16, 99});
    s = s21_ii_empty.insert({16, 99});
    std_ii_it = t.first;
    s21_ii_it = s.first;

    EXPECT_EQ(t.second, s.second);
    EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
    EXPECT_EQ(std_ii_it->second, s21_ii_it->second);
  }
  {
    std::pair<std::map<int, std::string>::iterator, bool> t;
    std::pair<s21::map<int, std::string>::iterator, bool> s;

    t = std_is.insert({10, "Granat"});
    s = s21_is.insert({10, "Granat"});
    std_is_it = t.first;
    s21_is_it = s.first;

    EXPECT_EQ(t.second, s.second);
    EXPECT_EQ(std_is_it->first, s21_is_it->first);
    EXPECT_EQ(std_is_it->second, s21_is_it->second);

    t = std_is.insert({10, "Granat"});
    s = s21_is.insert({10, "Granat"});
    std_is_it = t.first;
    s21_is_it = s.first;

    EXPECT_EQ(t.second, s.second);
    EXPECT_EQ(std_is_it->first, s21_is_it->first);
    EXPECT_EQ(std_is_it->second, s21_is_it->second);
  }
}

TEST_F(S21MapTest, InsertKeyT) {
  {
    std::pair<std::map<int, int>::iterator, bool> t;
    std::pair<s21::map<int, int>::iterator, bool> s;

    t = std_ii.insert({16, 100});
    s = s21_ii.insert(16, 100);
    std_ii_it = t.first;
    s21_ii_it = s.first;

    EXPECT_EQ(t.second, s.second);
    EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
    EXPECT_EQ(std_ii_it->second, s21_ii_it->second);

    t = std_ii.insert({16, 99});
    s = s21_ii.insert(16, 99);
    std_ii_it = t.first;
    s21_ii_it = s.first;

    EXPECT_EQ(t.second, s.second);
    EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
    EXPECT_EQ(std_ii_it->second, s21_ii_it->second);
  }
  {
    std::pair<std::map<int, int>::iterator, bool> t;
    std::pair<s21::map<int, int>::iterator, bool> s;

    t = std_ii_empty.insert({16, 100});
    s = s21_ii_empty.insert(16, 100);
    std_ii_it = t.first;
    s21_ii_it = s.first;

    EXPECT_EQ(t.second, s.second);
    EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
    EXPECT_EQ(std_ii_it->second, s21_ii_it->second);

    t = std_ii_empty.insert({16, 99});
    s = s21_ii_empty.insert(16, 99);
    std_ii_it = t.first;
    s21_ii_it = s.first;

    EXPECT_EQ(t.second, s.second);
    EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
    EXPECT_EQ(std_ii_it->second, s21_ii_it->second);
  }
  {
    std::pair<std::map<int, std::string>::iterator, bool> t;
    std::pair<s21::map<int, std::string>::iterator, bool> s;

    t = std_is.insert({10, "Granat"});
    s = s21_is.insert(10, "Granat");
    std_is_it = t.first;
    s21_is_it = s.first;

    EXPECT_EQ(t.second, s.second);
    EXPECT_EQ(std_is_it->first, s21_is_it->first);
    EXPECT_EQ(std_is_it->second, s21_is_it->second);

    t = std_is.insert({10, ""});
    s = s21_is.insert(10, "");
    std_is_it = t.first;
    s21_is_it = s.first;

    EXPECT_EQ(t.second, s.second);
    EXPECT_EQ(std_is_it->first, s21_is_it->first);
    EXPECT_EQ(std_is_it->second, s21_is_it->second);
  }
}

TEST_F(S21MapTest, InsertOrAssign) {
  {
    std::pair<std::map<int, int>::iterator, bool> t;
    std::pair<s21::map<int, int>::iterator, bool> s;
    t = std_ii.insert_or_assign(10, 100);
    s = s21_ii.insert_or_assign(10, 100);
    std_ii_it = t.first;
    s21_ii_it = s.first;

    EXPECT_EQ(t.second, s.second);
    EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
    EXPECT_EQ(std_ii_it->second, s21_ii_it->second);

    t = std_ii.insert_or_assign(10, 99);
    s = s21_ii.insert_or_assign(10, 99);
    std_ii_it = t.first;
    s21_ii_it = s.first;

    EXPECT_EQ(t.second, s.second);
    EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
    EXPECT_EQ(std_ii_it->second, s21_ii_it->second);
  }
  {
    std::pair<std::map<int, int>::iterator, bool> t;
    std::pair<s21::map<int, int>::iterator, bool> s;

    t = std_ii_empty.insert_or_assign(16, 100);
    s = s21_ii_empty.insert_or_assign(16, 100);
    std_ii_it = t.first;
    s21_ii_it = s.first;

    EXPECT_EQ(t.second, s.second);
    EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
    EXPECT_EQ(std_ii_it->second, s21_ii_it->second);

    t = std_ii_empty.insert_or_assign(16, 99);
    s = s21_ii_empty.insert_or_assign(16, 99);
    std_ii_it = t.first;
    s21_ii_it = s.first;

    EXPECT_EQ(t.second, s.second);
    EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
    EXPECT_EQ(std_ii_it->second, s21_ii_it->second);
  }
  {
    std::pair<std::map<int, std::string>::iterator, bool> t;
    std::pair<s21::map<int, std::string>::iterator, bool> s;

    t = std_is.insert_or_assign(10, "Granat");
    s = s21_is.insert_or_assign(10, "Granat");
    std_is_it = t.first;
    s21_is_it = s.first;

    EXPECT_EQ(t.second, s.second);
    EXPECT_EQ(std_is_it->first, s21_is_it->first);
    EXPECT_EQ(std_is_it->second, s21_is_it->second);

    t = std_is.insert_or_assign(10, "Test");
    s = s21_is.insert_or_assign(10, "Test");
    std_is_it = t.first;
    s21_is_it = s.first;

    EXPECT_EQ(t.second, s.second);
    EXPECT_EQ(std_is_it->first, s21_is_it->first);
    EXPECT_EQ(std_is_it->second, s21_is_it->second);
  }
}

TEST_F(S21MapTest, Erase) {
  std_si_end = std_si.end();
  std_si_it = std_si.begin();
  s21_si_it = s21_si.begin();
  ++std_si_it;
  ++s21_si_it;
  std_si.erase(std_si_it);
  s21_si.erase(s21_si_it);
  EXPECT_EQ(std_si.size(), s21_si.size());

  std_si_it = std_si.begin();
  s21_si_it = s21_si.begin();
  for (; std_si_it != std_si_end;
       std_si_it = std_si.begin(), s21_si_it = s21_si.begin()) {
    std_si.erase(std_si_it);
    s21_si.erase(s21_si_it);
    EXPECT_EQ(std_si_it->first, s21_si_it->first);
    EXPECT_EQ(std_si_it->second, s21_si_it->second);
    // print(std_si_it, s21_si_it);
  }
  EXPECT_EQ(std_si.size(), s21_si.size());

  std_ss_it = std_ss.begin();
  s21_ss_it = s21_ss.begin();
  std_ss.erase(std_ss_it++);
  s21_ss.erase(s21_ss_it++);

  EXPECT_EQ(std_ss_it->first, s21_ss_it->first);
  EXPECT_EQ(std_ss_it->second, s21_ss_it->second);
  EXPECT_EQ(std_ss.size(), s21_ss.size());

  std_ss.erase(std_ss_it);
  s21_ss.erase(s21_ss_it);

  EXPECT_EQ(std_ss_it->first, s21_ss_it->first);
  EXPECT_EQ(std_ss_it->second, s21_ss_it->second);
  EXPECT_EQ(std_ss.size(), s21_ss.size());
}

TEST_F(S21MapTest, Swap) {
  std_ic_it = std_ic.begin();
  s21_ic_it = s21_ic.begin();

  std_ic_empty.swap(std_ic);
  s21_ic_empty.swap(s21_ic);

  std_ic_end = std_ic_empty.end();

  EXPECT_EQ(std_ic.size(), s21_ic.size());
  EXPECT_EQ(std_ic_empty.size(), s21_ic_empty.size());

  for (; std_ic_it != std_ic_end; ++std_ic_it, ++s21_ic_it) {
    EXPECT_EQ(std_ic_it->first, s21_ic_it->first);
    EXPECT_EQ(std_ic_it->second, s21_ic_it->second);
    // print(std_ic_it, s21_ic_it);
  }
  std_ii_it = std_ii.begin();
  s21_ii_it = s21_ii.begin();

  std_ii.swap(std_ii);
  s21_ii.swap(s21_ii);

  std_ii_end = std_ii.end();

  EXPECT_EQ(std_ii.size(), s21_ii.size());

  for (; std_ii_it != std_ii_end; ++std_ii_it, ++s21_ii_it) {
    EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
    EXPECT_EQ(std_ii_it->second, s21_ii_it->second);
    // print(std_ii_it, s21_ii_it);
  }
}

TEST_F(S21MapTest, Merge) {
  std::map<int, int> mt{{16, 160}, {10, 100}, {11, 110}, {20, 200}};
  s21::map<int, int> ms{{16, 160}, {10, 100}, {11, 110}, {20, 200}};
  std_ii_it = mt.begin();
  s21_ii_it = ms.begin();

  std_ii.merge(mt);
  s21_ii.merge(ms);
  std_ii_end = std_ii.end();

  EXPECT_EQ(mt.size(), ms.size());
  EXPECT_EQ(std_ii.size(), s21_ii.size());
  for (; std_ii_it != std_ii_end; ++std_ii_it, ++s21_ii_it) {
    EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
    EXPECT_EQ(std_ii_it->second, s21_ii_it->second);
    // print(std_ii_it, s21_ii_it);
  }

  std::map<std::string, int> mts{{"Guava", 20},
                                 {"Persimmon", 21},
                                 {"Papaya", 22},
                                 {"Lime", 23},
                                 {"AA", 1}};
  s21::map<std::string, int> mss{{"Guava", 20},
                                 {"Persimmon", 21},
                                 {"Papaya", 22},
                                 {"Lime", 23},
                                 {"AA", 1}};
  std_si_it = mts.begin();
  s21_si_it = mss.begin();

  std_si.merge(mts);
  s21_si.merge(mss);
  std_si_end = std_si.end();

  EXPECT_EQ(mts.size(), mss.size());
  EXPECT_EQ(std_si.size(), s21_si.size());
  for (; std_si_it != std_si_end; ++std_si_it, ++s21_si_it) {
    EXPECT_EQ(std_si_it->first, s21_si_it->first);
    EXPECT_EQ(std_si_it->second, s21_si_it->second);
    // print(std_si_it, s21_si_it);
  }
}

TEST_F(S21MapTest, Contains) {
  EXPECT_TRUE(s21_ic.contains(8));
  EXPECT_TRUE(s21_ii.contains(20));
  EXPECT_TRUE(s21_si.contains("Fig"));
  EXPECT_TRUE(s21_is.contains(3));

  EXPECT_FALSE(s21_ic.contains(-8));
  EXPECT_FALSE(s21_ii.contains(16));
  EXPECT_FALSE(s21_si.contains("Lime"));
  EXPECT_FALSE(s21_is.contains(10));
  EXPECT_FALSE(s21_si_empty.contains(""));
}

TEST_F(S21MapTest, InsertMany) {
  {
    std::pair p1 = {30, 100}, p2 = {31, 101}, p3 = {20, 200}, p4 = {30, -100};
    std_ii.insert({p1, p2, p3, p4});
    std::vector<std::pair<s21::map<int, int>::iterator, bool>> vec =
        s21_ii.insert_many(p1, p2, p3, p4);

    s21_ii_it = s21_ii.begin();
    std_ii_it = std_ii.begin();
    std_ii_end = std_ii.end();
    EXPECT_TRUE(vec[0].second);
    EXPECT_TRUE(vec[1].second);
    EXPECT_FALSE(vec[2].second);
    EXPECT_FALSE(vec[3].second);

    for (; std_ii_it != std_ii_end; ++std_ii_it, ++s21_ii_it) {
      EXPECT_EQ(std_ii_it->first, s21_ii_it->first);
      EXPECT_EQ(std_ii_it->second, s21_ii_it->second);
      // print(std_ii_it, s21_ii_it);
    }
  }
  {
    std::pair<std::string, int> p1 = {"Lemon", 11}, p2 = {"Lime", 20},
                                p3 = {"Guava", 112}, p4 = {"Lime", -100};
    std_si.insert({p1, p2, p3, p4});
    auto vec = s21_si.insert_many(p1, p2, p3, p4);

    s21_si_it = s21_si.begin();
    std_si_it = std_si.begin();
    std_si_end = std_si.end();
    EXPECT_FALSE(vec[0].second);
    EXPECT_TRUE(vec[1].second);
    EXPECT_TRUE(vec[2].second);
    EXPECT_FALSE(vec[3].second);

    for (; std_si_it != std_si_end; ++std_si_it, ++s21_si_it) {
      EXPECT_EQ(std_si_it->first, s21_si_it->first);
      EXPECT_EQ(std_si_it->second, s21_si_it->second);
      // print(std_si_it, s21_si_it);
    }
    // s21_si.print();
  }
}

TEST_F(S21MapTest, Greater) {
  std::map<std::string, int, std::greater<std::string>> tgr = {
      {"Lemon", 10},  {"Pear", 11},   {"Mango", 12}, {"Apple", 13},
      {"Banana", 14}, {"Orange", 15}, {"Grape", 16}, {"Coconut", 17},
      {"Kiwi", 18},   {"Fig", 19}};
  s21::map<std::string, int, std::greater<std::string>> sgr = {
      {"Lemon", 10},  {"Pear", 11},   {"Mango", 12}, {"Apple", 13},
      {"Banana", 14}, {"Orange", 15}, {"Grape", 16}, {"Coconut", 17},
      {"Kiwi", 18},   {"Fig", 19}};
  std::map<std::string, int, std::greater<std::string>>::iterator
      it = tgr.begin(),
      end = tgr.end();
  s21::map<std::string, int, std::greater<std::string>>::iterator is =
      sgr.begin();

  for (; it != end; ++it, ++is) {
    EXPECT_EQ(it->first, is->first);
    EXPECT_EQ(it->second, is->second);
    // print(it, is);
  }
}
