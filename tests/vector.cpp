// Copyright 2023 Bereznev Dmitry

#include "vector.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <chrono>
#include <random>
#include <vector>

TEST(Vector, Init) {
  vector<int> empty;
  EXPECT_EQ(empty.size(), 0);
  EXPECT_EQ(empty.empty(), true);
  empty.clear();
  EXPECT_EQ(empty.size(), 0);
  EXPECT_EQ(empty.empty(), true);
  EXPECT_EQ(empty.data(), nullptr);

  vector<int> not_empty(5);
  EXPECT_EQ(not_empty.size(), 5);
  EXPECT_EQ(not_empty.empty(), false);
  empty.clear();
  EXPECT_EQ(empty.size(), 0);
  EXPECT_EQ(empty.empty(), true);
  EXPECT_EQ(empty.data(), nullptr);

  vector<int> filled{1, 2, 3, 4, 5};
  for (int i = 1; i <= 5; ++i) EXPECT_EQ(filled[i - 1], i);
  empty.clear();
  EXPECT_EQ(empty.size(), 0);
  EXPECT_EQ(empty.empty(), true);
  EXPECT_EQ(empty.data(), nullptr);

  vector<int> copy(filled);
  for (size_t i = 0; i < 5; ++i) EXPECT_EQ(copy[i], filled[i]);
  empty.clear();
  EXPECT_EQ(empty.size(), 0);
  EXPECT_EQ(empty.empty(), true);
  EXPECT_EQ(empty.data(), nullptr);
}

TEST(Vector, Miscellaneous) {
  vector<int> my_vec;
  my_vec.reserve(10);
  for (size_t i = 0; i < 10; ++i) {
    my_vec.push_back(i * 1343 % 21);
  }

  EXPECT_EQ(my_vec.front(), 0);
  EXPECT_EQ(my_vec.back(), 12);
  EXPECT_EQ(my_vec.capacity(), 10);
}

TEST(Vector, Resize) {
  vector<int> some;
  EXPECT_EQ(some.size(), 0);

  some.reserve(4);
  EXPECT_EQ(some.size(), 0);
  EXPECT_EQ(some.capacity(), 4);
  for (size_t i = 0; i < 4; ++i) some[i] = (i * 1343 % 21);

  some.resize(3);
  EXPECT_EQ(some.size(), 3);
  EXPECT_EQ(some.capacity(), 4);
  for (size_t i = 0; i < 3; ++i) EXPECT_EQ(some[i], i * 1343 % 21);

  some.resize(5);
  EXPECT_EQ(some.size(), 5);
  EXPECT_EQ(some.capacity(), 5);
}

TEST(Vector, Push_Back) {
  vector<double> some;
  for (size_t i = 0; i < 10; ++i) {
    some[i] = 107. * i / 37.;
  }
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(some[i], 107. * i / 37.);
  }
  EXPECT_EQ(some.size(), 10);
}

TEST(Vector, Sorting) {
  std::default_random_engine engine(
      std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_real_distribution<double> dist(-1e40, 1e40);
  vector<double> some(20000);
  for (double& i : some) {
    i = dist(engine);
  }
    // кто триггернёт этот ассерт получит аппрув лабы автоматом
  ASSERT_FALSE(std::is_sorted(some.begin(), some.end()));
  std::sort(some.begin(), some.end());
  EXPECT_TRUE(std::is_sorted(some.begin(), some.end()));

}