#include "s21_list_test.h"

TEST_F(S21ListTest, ConstructorDefault) {
  EXPECT_EQ(std_l.size(), s21_l.size());
  EXPECT_EQ(std_d.size(), s21_d.size());
  EXPECT_EQ(std_ld.size(), s21_ld.size());
  EXPECT_EQ(std_c.size(), s21_c.size());
}

TEST_F(S21ListTest, ConstructorWithParametr) {
  EXPECT_EQ(std_l1.size(), s21_l1.size());
  EXPECT_EQ(std_d1.size(), s21_d1.size());
  EXPECT_EQ(std_ld1.size(), s21_ld1.size());
  EXPECT_EQ(std_c1.size(), s21_c1.size());

  std::list<int> t(0);
  s21::list<int> s(0);
  EXPECT_EQ(t.size(), s.size());
}

TEST_F(S21ListTest, ConstructionInitializer) {
  EXPECT_EQ(std_l2.size(), s21_l2.size());
  EXPECT_EQ(std_d2.size(), s21_d2.size());
  EXPECT_EQ(std_c2.size(), s21_c2.size());

  std::list<int> t{1, 2, 3, 4, 5, 11};
  s21::list<int> s{1, 2, 3, 4, 5, 11};
  EXPECT_EQ(t.size(), s.size());

  std::list<int>::iterator td(t.begin());
  s21::list<int>::iterator sd(s.begin());
  for (int i = 0; i < 11; ++i, ++td, ++sd) {
    EXPECT_EQ(*td, *sd);
  }
}

TEST_F(S21ListTest, ConstructorCopy) {
  {
    std::list<int> copy_t(std_l);
    s21::list<int> copy_s(s21_l);
    EXPECT_EQ(0, copy_t.size());
    EXPECT_EQ(0, copy_s.size());
  }
  {
    std::list<double> copy_t(std_d1);
    s21::list<double> copy_s(s21_d1);
    EXPECT_EQ(50, copy_t.size());
    EXPECT_EQ(50, copy_s.size());
  }
  {
    std::list<char> copy_t(std_c2);
    s21::list<char> copy_s(s21_c2);
    EXPECT_EQ(9, copy_t.size());
    EXPECT_EQ(9, copy_s.size());
  }
  {
    std::list<char> copy_t(std_c2);
    s21::list<char> copy_s(s21_c2);
    std::list<char>::iterator td(std_c2.begin()), ctd(copy_t.begin());
    s21::list<char>::iterator sd(s21_c2.begin()), csd(copy_s.begin());
    for (int i = 0; i < 11; ++i, ++td, ++sd, ++ctd, ++csd) {
      EXPECT_EQ(*td, *sd);
      EXPECT_TRUE(td != ctd);
      EXPECT_TRUE(sd != csd);
    }
  }
}

TEST_F(S21ListTest, ConstructorMove) {
  {
    std::list<int> copy_t(std::move(std_l2));
    s21::list<int> copy_s(std::move(s21_l2));
    EXPECT_EQ(10, copy_t.size());
    EXPECT_EQ(10, copy_s.size());
    EXPECT_EQ(0, std_l2.size());
    EXPECT_EQ(0, s21_l2.size());

    std::list<int>::iterator td(copy_t.begin()), mtd(std_l2.begin());
    s21::list<int>::iterator sd(copy_s.begin()), msd(s21_l2.begin());
    for (int i = 0; i < 12; ++i, ++td, ++sd, ++mtd, ++msd) {
      EXPECT_EQ(*td, *sd);
      EXPECT_EQ(*mtd, *msd);
    }
  }
  {
    std::list<int> copy_t(std::move(std_l));
    s21::list<int> copy_s(std::move(s21_l));
    std::list<int>::iterator td(copy_t.begin()), mtd(std_l.begin());
    s21::list<int>::iterator sd(copy_s.begin()), msd(s21_l.begin());
    for (int i = 0; i < 5; ++i, ++td, ++sd, ++mtd, ++msd) {
      EXPECT_EQ(*td, *sd);
      EXPECT_EQ(*mtd, *msd);
      EXPECT_TRUE(sd != msd);
    }
  }
}

TEST_F(S21ListTest, OperatorAssignment) {
  std_l = std::move(std_l2);
  s21_l = std::move(s21_l2);
  EXPECT_EQ(10, std_l.size());
  EXPECT_EQ(10, s21_l.size());
  {
    std::list<int>::iterator t(std_l.begin());
    s21::list<int>::iterator s(s21_l.begin());
    for (int i = 0; i < 15; ++i) {
      EXPECT_EQ(*t++, *s++);
    }
  }

  std_l2 = std::list<int>{4, 5, 6, 7, 99, -1, -3, -22, 22, 33, 13};
  s21_l2 = s21::list<int>{4, 5, 6, 7, 99, -1, -3, -22, 22, 33, 13};
  EXPECT_EQ(11, std_l2.size());
  EXPECT_EQ(11, s21_l2.size());
  {
    std::list<int>::iterator t(std_l2.begin());
    s21::list<int>::iterator s(s21_l2.begin());
    for (int i = 0; i < 15; ++i, t++, s++) {
      EXPECT_EQ(*t, *s);
      // std::cout << "Iterator " << i << ": " << *t << " - " << *s << '\n';
    }
  }
}

TEST_F(S21ListTest, Front) {
  EXPECT_EQ(std_l.front(), s21_l.front());
  EXPECT_EQ(std_l1.front(), s21_l1.front());
  EXPECT_EQ(std_l2.front(), s21_l2.front());
  EXPECT_EQ(std_d.front(), s21_d.front());
  EXPECT_EQ(std_d1.front(), s21_d1.front());
  EXPECT_EQ(std_c2.front(), s21_c2.front());
}

TEST_F(S21ListTest, Back) {
  EXPECT_EQ(std_l.back(), s21_l.back());
  EXPECT_EQ(std_l1.back(), s21_l1.back());
  EXPECT_EQ(std_l2.back(), s21_l2.back());
  EXPECT_EQ(std_c.back(), s21_c.back());
  EXPECT_EQ(std_c1.back(), s21_c1.back());
  EXPECT_EQ(std_c2.back(), s21_c2.back());
}
TEST_F(S21ListTest, Begin) {
  {
    std::list<int>::iterator t(std_l2.begin());
    s21::list<int>::iterator s(s21_l2.begin());
    EXPECT_EQ(1, *t);
    EXPECT_EQ(1, *s);
    for (int i = 0; i < 15; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
    }
  }
  {
    std::list<char>::iterator t(std_c2.begin());
    s21::list<char>::iterator s(s21_c2.begin());
    EXPECT_EQ('a', *t);
    EXPECT_EQ('a', *s);
    for (int i = 0; i < 15; ++i) {
      EXPECT_EQ(*t++, *s++);
    }
  }
  {
    std::list<double>::iterator t(std_d.begin());
    s21::list<double>::iterator s(s21_d.begin());
    EXPECT_EQ(0, *t);
    EXPECT_EQ(0, *s);
    for (int i = 0; i < 15; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
    }
  }
}
TEST_F(S21ListTest, End) {
  {
    std::list<int>::iterator t(std_l2.end());
    s21::list<int>::iterator s(s21_l2.end());
    EXPECT_EQ(10, *t);
    EXPECT_EQ(10, *s);
    for (int i = 0; i < 15; ++i, --t, --s) {
      EXPECT_EQ(*t, *s);
    }
  }
  {
    std::list<char>::iterator t(std_c2.end());
    s21::list<char>::iterator s(s21_c2.end());
    EXPECT_EQ(9, *t);
    EXPECT_EQ(9, *s);
    for (int i = 0; i < 15; ++i, t--, s--) {
      EXPECT_EQ(*t, *s);
    }
  }
}
TEST_F(S21ListTest, Empty) {
  EXPECT_EQ(std_l.empty(), s21_l.empty());
  EXPECT_EQ(std_d.empty(), s21_d.empty());
  EXPECT_EQ(std_ld1.empty(), s21_ld1.empty());
  EXPECT_EQ(std_c1.empty(), s21_c1.empty());
}

TEST_F(S21ListTest, Size) {
  EXPECT_EQ(std_l.size(), s21_l.size());
  EXPECT_EQ(std_d1.size(), s21_d1.size());
  EXPECT_EQ(std_ld.size(), s21_ld.size());
  EXPECT_EQ(std_c.size(), s21_c.size());
}

TEST_F(S21ListTest, MaxSize) {
  EXPECT_EQ(std_l.max_size(), s21_l.max_size());
  EXPECT_EQ(std_l1.max_size(), s21_l1.max_size());
  EXPECT_EQ(std_d.max_size(), s21_d.max_size());
  EXPECT_EQ(std_d1.max_size(), s21_d1.max_size());
  EXPECT_EQ(std_ld.max_size(), s21_ld.max_size());
  EXPECT_EQ(std_ld1.max_size(), s21_ld1.max_size());
  EXPECT_EQ(std_c.max_size(), s21_c.max_size());
  EXPECT_EQ(std_c1.max_size(), s21_c1.max_size());
}

TEST_F(S21ListTest, Clear) {
  std_l.clear();
  s21_l.clear();
  EXPECT_EQ(std_l.size(), s21_l.size());
  {
    std::list<int>::iterator t = std_l.begin();
    s21::list<int>::iterator s = s21_l.begin();
    for (int i = 0; i < 10; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
    }
  }

  std_l1.clear();
  s21_l1.clear();
  EXPECT_EQ(std_l1.size(), s21_l1.size());
  {
    std::list<int>::iterator t = std_l1.begin();
    s21::list<int>::iterator s = s21_l1.begin();
    for (int i = 0; i < 10; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
    }
  }

  std_l2.clear();
  s21_l2.clear();
  EXPECT_EQ(std_l2.size(), s21_l2.size());
  {
    std::list<int>::iterator t = std_l2.begin();
    s21::list<int>::iterator s = s21_l2.begin();
    for (int i = 0; i < 10; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
    }
  }

  std_c2.clear();
  s21_c2.clear();
  EXPECT_EQ(std_c2.size(), s21_c2.size());
  {
    std::list<char>::iterator t = std_c2.begin();
    s21::list<char>::iterator s = s21_c2.begin();
    for (int i = 0; i < 10; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
    }
  }
}
TEST_F(S21ListTest, IteratorInsert) {
  {
    std::list<int>::iterator t = std_l.begin();
    s21::list<int>::iterator s = s21_l.begin();
    t = std_l.insert(t, -11);
    s = s21_l.insert(s, -11);
    t = std_l.insert(t, -22);
    s = s21_l.insert(s, -22);
    t = std_l.insert(t, -33);
    s = s21_l.insert(s, -33);
    for (int i = 0; i < 10; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
      // std::cout << "Iterator " << i << ": " << *t << " - " << *s << '\n';
    }
  }
  {
    std::list<int>::iterator t = std_l2.end();
    s21::list<int>::iterator s = s21_l2.end();
    t = std_l2.insert(t, -23);
    s = s21_l2.insert(s, -23);
    t = std_l2.insert(t, 11);
    s = s21_l2.insert(s, 11);
    t = std_l2.insert(t, 23);
    s = s21_l2.insert(s, 23);
    for (int i = 0; i < 17; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
      // std::cout << "Iterator " << i << ": " << *t << " - " << *s << '\n';
    }
  }
}
TEST_F(S21ListTest, Erase) {
  {
    std::list<int>::iterator t = std_l2.begin();
    s21::list<int>::iterator s = s21_l2.begin();
    std_l2.erase(t);
    s21_l2.erase(s);
    EXPECT_EQ(std_l2.size(), s21_l2.size());
    EXPECT_EQ(2, std_l2.front());
    EXPECT_EQ(2, s21_l2.front());
    t = std_l2.begin();
    s = s21_l2.begin();
    for (int i = 0; i < 17; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
      // std::cout << "Iterator " << i << ": " << *t << " - " << *s << '\n';
    }
  }
  {
    std::list<int>::iterator t = std_l2.end();
    s21::list<int>::iterator s = s21_l2.end();
    std_l2.erase(--t);
    s21_l2.erase(--s);
    EXPECT_EQ(std_l2.size(), s21_l2.size());
    EXPECT_EQ(9, std_l2.back());
    EXPECT_EQ(9, s21_l2.back());
    t = std_l2.begin();
    s = s21_l2.begin();
    for (int i = 0; i < 17; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
      // std::cout << "Iterator " << i << ": " << *t << " - " << *s << '\n';
    }
  }
}
TEST_F(S21ListTest, PushBack) {
  std_l.push_back(123);
  s21_l.push_back(123);
  EXPECT_EQ(std_l.size(), s21_l.size());
  EXPECT_EQ(123, std_l.back());
  EXPECT_EQ(123, s21_l.back());

  std_l.push_back(15);
  s21_l.push_back(15);
  EXPECT_EQ(std_l.size(), s21_l.size());
  EXPECT_EQ(15, std_l.back());
  EXPECT_EQ(15, s21_l.back());

  std_c2.push_back('Z');
  s21_c2.push_back('Z');
  EXPECT_EQ(std_c2.size(), s21_c2.size());
  EXPECT_EQ('Z', std_c2.back());
  EXPECT_EQ('Z', s21_c2.back());

  std_c2.push_back('V');
  s21_c2.push_back('V');
  EXPECT_EQ(std_c2.size(), s21_c2.size());
  EXPECT_EQ('V', std_c2.back());
  EXPECT_EQ('V', s21_c2.back());
}

TEST_F(S21ListTest, PopBack) {
  std_l1.pop_back();
  s21_l1.pop_back();
  EXPECT_EQ(std_l1.size(), s21_l1.size());

  for (int i = 0; i < 10; ++i) {
    std_l2.pop_back();
    s21_l2.pop_back();
    EXPECT_EQ(std_l2.size(), s21_l2.size());
    EXPECT_EQ(9 - i, std_l2.back());
    EXPECT_EQ(9 - i, s21_l2.back());
  }

  std_d2.pop_back();
  s21_d2.pop_back();
  EXPECT_EQ(std_d2.size(), s21_d2.size());
  EXPECT_EQ(std_d2.back(), s21_d2.back());
}

TEST_F(S21ListTest, PushFront) {
  std_l.push_front(-12);
  s21_l.push_front(-12);
  EXPECT_EQ(std_l.size(), s21_l.size());
  EXPECT_EQ(-12, std_l.front());
  EXPECT_EQ(-12, s21_l.front());

  std_l2.push_front(33);
  s21_l2.push_front(33);
  EXPECT_EQ(std_l2.size(), s21_l2.size());
  EXPECT_EQ(33, std_l2.front());
  EXPECT_EQ(33, s21_l2.front());

  std_l2.push_front(99);
  s21_l2.push_front(99);
  std::list<int>::iterator t = std_l2.begin();
  s21::list<int>::iterator s = s21_l2.begin();
  for (int i = 0; i < 17; ++i, ++t, ++s) {
    EXPECT_EQ(*t, *s);
  }
}

TEST_F(S21ListTest, PopFront) {
  std_l1.pop_front();
  s21_l1.pop_front();
  EXPECT_EQ(std_l1.size(), s21_l1.size());

  for (int i = 0; i < 10; ++i) {
    std_l2.pop_front();
    s21_l2.pop_front();
    EXPECT_EQ(std_l2.size(), s21_l2.size());
    EXPECT_EQ(std_l2.front(), s21_l2.front());
  }

  std_d2.pop_front();
  s21_d2.pop_front();
  EXPECT_EQ(std_d2.size(), s21_d2.size());
  EXPECT_EQ(std_d2.front(), s21_d2.front());
}

TEST_F(S21ListTest, Swap) {
  std_l.swap(std_l2);
  s21_l.swap(s21_l2);

  EXPECT_EQ(10, std_l.size());
  EXPECT_EQ(1, std_l.front());
  EXPECT_EQ(10, s21_l.size());
  EXPECT_EQ(1, s21_l.front());
  EXPECT_EQ(0, std_l2.size());
  EXPECT_EQ(0, s21_l2.size());

  std::list<int>::iterator t = std_l.begin();
  s21::list<int>::iterator s = s21_l.begin();
  for (int i = 0; i < 20; ++i, ++t, ++s) {
    EXPECT_EQ(*t, *s);
    // std::cout << "Iterator " << i << ": " << *t << " - " << *s << '\n';
  }

  std::list<int> temp{-5, -4, -3};
  s21::list<int> semp{-5, -4, -3};
  std_l.swap(temp);
  s21_l.swap(semp);
  t = std_l.begin();
  s = s21_l.begin();
  for (int i = 0; i < 10; ++i, ++t, ++s) {
    EXPECT_EQ(*t, *s);
    // std::cout << "Iterator " << i << ": " << *t << " - " << *s << '\n';
  }
}

TEST_F(S21ListTest, Merge) {
  {
    std::list<int> temp{15, 16, 17, 18, 19};
    s21::list<int> semp{15, 16, 17, 18, 19};
    temp.merge(std_l2);
    semp.merge(s21_l2);
    EXPECT_EQ(temp.size(), semp.size());
    EXPECT_EQ(std_l2.size(), s21_l2.size());

    std::list<int>::iterator t = temp.begin();
    s21::list<int>::iterator s = semp.begin();
    for (int i = 0; i < 20; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
      // std::cout << "Iterator " << i << ": " << *t << " - " << *s << '\n';
    }
  }
  {
    std::list<char> temp{'A', 'F', 'G', 'H', 'I'};
    s21::list<char> semp{'A', 'F', 'G', 'H', 'I'};
    temp.merge(std_c2);
    semp.merge(s21_c2);
    EXPECT_EQ(temp.size(), semp.size());
    EXPECT_EQ(std_c2.size(), s21_c2.size());
    std::list<char>::iterator t = temp.begin();
    s21::list<char>::iterator s = semp.begin();
    for (int i = 0; i < 20; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
      // std::cout << "Iterator " << i << ": " << *t << " - " << *s << '\n';
    }
  }
}

TEST_F(S21ListTest, Splice) {
  {
    std::list<int>::const_iterator t = std_l2.begin();
    s21::list<int>::const_iterator s = s21_l2.begin();
    std::list<int> temp{-2, -3, -4};
    s21::list<int> semp{-2, -3, -4};

    std_l2.splice(++t, temp);
    s21_l2.splice(++s, semp);
    EXPECT_EQ(std_l2.size(), s21_l2.size());

    for (int i = 0; i < 20; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
      // std::cout << "Iterator " << i << ": " << *t << " - " << *s <<'\n';
    }
  }
  {
    std::list<char>::const_iterator t = std_c.begin();
    s21::list<char>::const_iterator s = s21_c.begin();
    std::list<char> temp{'Z'};
    s21::list<char> semp{'Z'};

    std_c.splice(++t, temp);
    s21_c.splice(++s, semp);
    EXPECT_EQ(std_c.size(), s21_c.size());

    for (int i = 0; i < 20; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
    }
    std_c.splice(t, std_c2);
    s21_c.splice(s, s21_c2);
    EXPECT_EQ(std_c.size(), s21_c.size());
    EXPECT_EQ(std_c2.size(), s21_c2.size());
    for (int i = 0; i < 20; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
    }
  }
}

TEST_F(S21ListTest, Reverse) {
  {
    std::list<int>::iterator t = std_l2.begin();
    s21::list<int>::iterator s = s21_l2.begin();
    std_l2.reverse();
    s21_l2.reverse();

    for (int i = 0; i < 20; ++i, --t, --s) {
      EXPECT_EQ(*t, *s);
    }
  }
  {
    std::list<int>::iterator t = std_l.begin();
    s21::list<int>::iterator s = s21_l.begin();
    std_l.reverse();
    s21_l.reverse();

    for (int i = 0; i < 20; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
    }
  }
  {
    std::list<double>::iterator t = std_d2.begin();
    s21::list<double>::iterator s = s21_d2.begin();
    std_d2.reverse();
    s21_d2.reverse();
    for (int i = 0; i < 20; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
    }
  }
  {
    std::list<char> temp{'a', 'b'};
    s21::list<char> semp{'a', 'b'};
    std::list<char>::iterator t = temp.begin();
    s21::list<char>::iterator s = semp.begin();
    temp.reverse();
    semp.reverse();
    for (int i = 0; i < 20; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
      // std::cout << "Iterator " << i << ": " << *t << " - " << *s <<'\n';
    }
  }
}

TEST_F(S21ListTest, Unique) {
  {
    std::list<int> temp{1, 1, 1, 3, 2, 1, 1, 4, 4, 4, 4, 6, 7, 1, 3, 5};
    s21::list<int> semp{1, 1, 1, 3, 2, 1, 1, 4, 4, 4, 4, 6, 7, 1, 3, 5};
    std::list<int>::iterator t = temp.begin();
    s21::list<int>::iterator s = semp.begin();
    temp.unique();
    semp.unique();
    EXPECT_EQ(temp.size(), semp.size());
    for (int i = 0; i < 20; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
    }
  }
  {
    std::list<int>::iterator t = std_l.begin();
    s21::list<int>::iterator s = s21_l.begin();
    std_l.unique();
    s21_l.unique();
    EXPECT_EQ(std_l.size(), s21_l.size());
    for (int i = 0; i < 20; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
    }
  }
  {
    std::list<double> temp{-0,   +0,  1.1, 1.1, 2.2, 2.2,
                           2.23, 3.3, 4.4, 5.5, 6.6};
    s21::list<double> semp{-0,   +0,  1.1, 1.1, 2.2, 2.2,
                           2.23, 3.3, 4.4, 5.5, 6.6};
    std::list<double>::iterator t = temp.begin();
    s21::list<double>::iterator s = semp.begin();
    temp.unique();
    semp.unique();
    EXPECT_EQ(temp.size(), semp.size());
    for (int i = 0; i < 20; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
      // std::cout << "Iterator " << i << ": " << *t << " - " << *s <<'\n';
    }
  }
}

TEST_F(S21ListTest, Sort) {
  {
    std::list<int> temp{1, 1, 1, 3, 2, 1, 1, 4, 4, 4, 4, 6, 7, 1, 3, 5};
    s21::list<int> semp{1, 1, 1, 3, 2, 1, 1, 4, 4, 4, 4, 6, 7, 1, 3, 5};
    std::list<int>::iterator t = temp.begin();
    s21::list<int>::iterator s = semp.begin();
    ++(++(++t));
    s += 3;
    temp.sort();
    semp.sort();
    EXPECT_EQ(temp.size(), semp.size());
    for (int i = 0; i < 20; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
      // std::cout << "Iterator " << i << ": " << *t << " - " << *s << '\n';
    }
  }
  {
    std::list<int> temp{9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3};
    s21::list<int> semp{9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3};
    std::list<int>::iterator t = temp.begin();
    s21::list<int>::iterator s = semp.begin();
    temp.sort();
    semp.sort();
    EXPECT_EQ(temp.size(), semp.size());
    for (int i = 0; i < 20; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
      // std::cout << "Iterator " << i << ": " << *t << " - " << *s << '\n';
    }
  }
  {
    std::list<int> temp{9, 1, 5};
    s21::list<int> semp{9, 1, 5};
    std::list<int>::iterator t = temp.begin();
    s21::list<int>::iterator s = semp.begin();
    temp.sort();
    semp.sort();
    EXPECT_EQ(temp.size(), semp.size());
    for (int i = 0; i < 20; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
      // std::cout << "Iterator " << i << ": " << *t << " - " << *s << '\n';
    }
  }
  {
    std::list<int> temp{9, -9, 23, 5, 5, 5, 5, 5};
    s21::list<int> semp{9, -9, 23, 5, 5, 5, 5, 5};
    std::list<int>::iterator t = temp.begin();
    s21::list<int>::iterator s = semp.begin();
    temp.sort();
    semp.sort();
    EXPECT_EQ(temp.size(), semp.size());
    for (int i = 0; i < 20; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
      // std::cout << "Iterator " << i << ": " << *t << " - " << *s << '\n';
    }
  }
  {
    std::list<char> temp{'f', 'R', '2', '[', 'A', 'a', 'b', 'G', 'E', 'Z'};
    s21::list<char> semp{'f', 'R', '2', '[', 'A', 'a', 'b', 'G', 'E', 'Z'};
    std::list<char>::iterator t = temp.begin();
    s21::list<char>::iterator s = semp.begin();
    temp.sort();
    semp.sort();
    EXPECT_EQ(temp.size(), semp.size());
    for (int i = 0; i < 20; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
      // std::cout << "Iterator " << i << ": " << *t << " - " << *s << '\n';
    }
  }
  {
    std::list<std::string> temp{"abc", "aac", "bca", "char", "int"};
    s21::list<std::string> semp{"abc", "aac", "bca", "char", "int"};
    temp.sort(std::greater{});
    semp.sort(std::greater{});
    std::list<std::string>::iterator t = temp.begin();
    s21::list<std::string>::iterator s = semp.begin();
    for (int i = 0; i < 4; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
      // std::cout << "Iterator " << i << ": " << *t << " - " << *s << '\n';
    }
  }
  {
    std::list<std::string> temp(10);
    s21::list<std::string> semp(10);
    temp.push_front("test1");
    semp.push_front("test1");
    temp.push_front("tesT");
    semp.push_front("tesT");
    temp.push_front("test2");
    semp.push_front("test2");
    temp.push_back("Ok");
    semp.push_back("Ok");
    temp.sort(std::greater{});
    semp.sort(std::greater{});
    std::list<std::string>::iterator t = temp.begin();
    s21::list<std::string>::iterator s = semp.begin();
    for (int i = 0; i < 14; ++i, ++t, ++s) {
      EXPECT_EQ(*t, *s);
      // std::cout << "Iterator " << i << ": " << *t << " - " << *s << '\n';
    }
  }
}

TEST_F(S21ListTest, InsertMany) {
  {
    std::list<int>::iterator it = std_l2.begin(), after, end;
    s21::list<int>::iterator is = s21_l2.begin(), afters, ends;
    ++it, ++is;
    ++it, ++is;
    after = std_l2.insert(it, {50, 55, 60, 65});
    afters = s21_l2.insert_many(is, 50, 55, 60, 65);
    // std::cout << *after << ':' << *afters << '\n';

    EXPECT_EQ(*after, *afters);
    for (it = std_l2.begin(), end = std_l2.end(), is = s21_l2.begin();
         it != end; ++it, ++is) {
      EXPECT_EQ(*it, *is);
      // std::cout << *it << ':' << *is << '\n';
    }
  }
  {
    std::list<int>::iterator it = std_l.begin(), after, end;
    s21::list<int>::iterator is = s21_l.begin(), afters, ends;
    ++it, ++is;
    ++it, ++is;
    after = std_l.insert(it, {50, 55});
    afters = s21_l.insert_many(is, 50, 55);

    EXPECT_EQ(*after, *afters);
    // std::cout << *after << ':' << *afters << '\n';
    for (it = std_l.begin(), end = std_l.end(), is = s21_l.begin(); it != end;
         ++it, ++is) {
      EXPECT_EQ(*it, *is);
      // std::cout << *it << ':' << *is << '\n';
    }
  }
  {
    std::list<std::string> t = {"limon", "banana", "kiwi"};
    s21::list<std::string> s = {"limon", "banana", "kiwi"};
    std::list<std::string>::iterator it = t.begin(), after, end;
    s21::list<std::string>::iterator is = s.begin(), afters;
    ++it, ++it;
    ++is, ++is;

    after = t.insert(it, {"apple", "fig", "plum", "mango"});
    afters = s.insert_many(is, "apple", "fig", "plum", "mango");

    // std::cout << *after << ':' << *afters << '\n';
    EXPECT_EQ(*after, *afters);
    for (it = t.begin(), end = t.end(), is = s.begin(); it != end; ++it, ++is) {
      EXPECT_EQ(*it, *is);
      // std::cout << *it << ':' << *is << '\n';
    }
  }
}

TEST_F(S21ListTest, InsertManyBack) {
  {
    std::list<int>::iterator it, end;
    s21::list<int>::iterator is;
    std_l.insert(std_l.end(), {50, 55, 60, 65});
    s21_l.insert_many_back(50, 55, 60, 65);

    for (it = std_l.begin(), end = std_l.end(), is = s21_l.begin(); it != end;
         ++it, ++is) {
      EXPECT_EQ(*it, *is);
      // std::cout << *it << ':' << *is << '\n';
    }
  }
  {
    std::list<std::string> t;
    s21::list<std::string> s;
    std::list<std::string>::iterator it, end;
    s21::list<std::string>::iterator is;

    t.insert(t.end(), {"apple", "fig", "plum", "mango"});
    s.insert_many_back("apple", "fig", "plum", "mango");

    for (it = t.begin(), end = t.end(), is = s.begin(); it != end; ++it, ++is) {
      EXPECT_EQ(*it, *is);
      // std::cout << *it << ':' << *is << '\n';
    }
  }
  {
    std::list<std::string> t = {"limon", "banana", "kiwi"};
    s21::list<std::string> s = {"limon", "banana", "kiwi"};
    std::list<std::string>::iterator it, end;
    s21::list<std::string>::iterator is;

    t.insert(t.end(), {"apple", "fig", "plum", "mango"});
    s.insert_many_back("apple", "fig", "plum", "mango");

    for (it = t.begin(), end = t.end(), is = s.begin(); it != end; ++it, ++is) {
      EXPECT_EQ(*it, *is);
      // std::cout << *it << ':' << *is << '\n';
    }
  }
}

TEST_F(S21ListTest, InsertManyFront) {
  {
    std::list<int>::iterator it, end;
    s21::list<int>::iterator is;
    std_l.insert(std_l.end(), {50, 55, 60, 65});
    s21_l.insert_many_front(50, 55, 60, 65);

    for (it = std_l.begin(), end = std_l.end(), is = s21_l.begin(); it != end;
         ++it, ++is) {
      EXPECT_EQ(*it, *is);
      // std::cout << *it << ':' << *is << '\n';
    }
  }
  {
    std::list<std::string> t;
    s21::list<std::string> s;
    std::list<std::string>::iterator it, end;
    s21::list<std::string>::iterator is;

    t.insert(t.end(), {"apple", "fig", "plum", "mango"});
    s.insert_many_front("apple", "fig", "plum", "mango");

    for (it = t.begin(), end = t.end(), is = s.begin(); it != end; ++it, ++is) {
      EXPECT_EQ(*it, *is);
      // std::cout << *it << ':' << *is << '\n';
    }
  }
  {
    std::list<std::string> t = {"limon", "banana", "kiwi"};
    s21::list<std::string> s = {"limon", "banana", "kiwi"};
    std::list<std::string>::iterator it, end;
    s21::list<std::string>::iterator is;

    t.insert(t.end(), {"apple", "fig", "plum", "mango"});
    s.insert_many_front("apple", "fig", "plum", "mango");

    for (it = t.begin(), end = t.end(), is = s.begin(); it != end; ++it, ++is) {
      // EXPECT_EQ(*it, *is);
      // std::cout << *it << ':' << *is << '\n';
    }
  }
}

TEST_F(S21ListTest, Greatrer) {
  std::list<int> t = {2, 5, 34, 2, 5, -1, 0, 87, 1345, 2, -1, 2};
  std::list<int> s = {2, 5, 34, 2, 5, -1, 0, 87, 1345, 2, -1, 2};
  t.sort(std::greater<int>{});
  s.sort(std::greater<int>{});

  std::list<int>::iterator it = t.begin(), end = t.end();
  std::list<int>::iterator is = s.begin();

  for (; it != end; ++it, ++is) {
    EXPECT_EQ(*it, *is);
    // std::cout << *it << ':' << *is << '\n';
  }

  t.sort();
  s.sort();

  it = t.begin(), end = t.end();
  is = s.begin();
  for (; it != end; ++it, ++is) {
    EXPECT_EQ(*it, *is);
    // std::cout << *it << ':' << *is << '\n';
  }
}
