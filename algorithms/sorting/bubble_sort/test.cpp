#include <algorithm>
#include <array>

#include <gtest/gtest.h>

#include "bubble_sort.hpp"

class Bubble_sort_f : public ::testing::Test
{
public:
  static constexpr std::array<int, 10UL> random_integers{ 81, 36, 65, 72, 12, 20, 34, 18, 3, 18 };
  static constexpr std::array<int, 10UL> sorted_integers{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  static constexpr std::array<int, 10UL> reverse_sorted_integers{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
  static constexpr std::array<int, 10UL> uniform_integers{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
  static constexpr std::array<int, 10UL> few_unique_integers{ 23, 23, 23, 42, 15, 4, 23, 23, 23, 42 };

  template <typename Container>
  void
  compare(Container lhs, Container rhs)
  {
    EXPECT_EQ(std::distance(std::cbegin(lhs), std::cend(lhs)), std::distance(std::cbegin(rhs), std::cend(rhs)));

    auto lhs_itr__ = std::cbegin(lhs);

    for(auto rhs_itr__ = std::cbegin(rhs), rhs_end__ = std::cend(rhs); rhs_itr__ != rhs_end__; ++lhs_itr__, ++rhs_itr__)
      {
        if(*lhs_itr__ != *rhs_itr__)
          FAIL();
      }
  }
};

TEST_F(Bubble_sort_f, Random_intergers)
{
  std::array<int, 10UL> a__ = Bubble_sort_f::random_integers;
  std::array<int, 10UL> b__ = Bubble_sort_f::random_integers;

  dsa::bubble_sort(a__.begin(), a__.end());
  std::sort(b__.begin(), b__.end(), std::less<int>());

  Bubble_sort_f::compare(a__, b__);
}

TEST_F(Bubble_sort_f, Sorted_integers)
{
  std::array<int, 10UL> a__ = Bubble_sort_f::sorted_integers;
  std::array<int, 10UL> b__ = Bubble_sort_f::sorted_integers;

  dsa::bubble_sort(a__.begin(), a__.end());
  std::sort(b__.begin(), b__.end(), std::less<int>());

  Bubble_sort_f::compare(a__, b__);
}

TEST_F(Bubble_sort_f, Reverse_sorted_integers)
{
  std::array<int, 10UL> a__ = Bubble_sort_f::reverse_sorted_integers;
  std::array<int, 10UL> b__ = Bubble_sort_f::reverse_sorted_integers;

  dsa::bubble_sort(a__.begin(), a__.end());
  std::sort(b__.begin(), b__.end(), std::less<int>());

  Bubble_sort_f::compare(a__, b__);
}

TEST_F(Bubble_sort_f, Uniform_integers)
{
  std::array<int, 10UL> a__ = Bubble_sort_f::uniform_integers;
  std::array<int, 10UL> b__ = Bubble_sort_f::uniform_integers;

  dsa::bubble_sort(a__.begin(), a__.end());
  std::sort(b__.begin(), b__.end(), std::less<int>());

  Bubble_sort_f::compare(a__, b__);
}

TEST_F(Bubble_sort_f, Few_unique_integers)
{
  std::array<int, 10UL> a__ = Bubble_sort_f::few_unique_integers;
  std::array<int, 10UL> b__ = Bubble_sort_f::few_unique_integers;

  dsa::bubble_sort(a__.begin(), a__.end());
  std::sort(b__.begin(), b__.end(), std::less<int>());

  Bubble_sort_f::compare(a__, b__);
}

int
main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}