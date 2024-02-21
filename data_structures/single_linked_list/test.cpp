#include <gtest/gtest.h>
#include <string>

#include "single_linked_list.hpp"

TEST(SingleLinkedListContainer, EmptyWhenEmpty)
{
  dsa::Single_linked_list<int> list;

  EXPECT_TRUE(list.empty());
}

TEST(SingleLinkedListContainer, BeginEqualEndWhenEmpty)
{
  dsa::Single_linked_list<int> list;

  EXPECT_EQ(list.begin(), list.end());
}

TEST(SingleLinkedListContainer, PushBackTrivialType)
{
  dsa::Single_linked_list<int> list;

  for(std::size_t i = 0, end = 9; i != end; ++i)
    {
      list.push_front(i);
    }

  auto itr = list.begin();

  for(std::size_t i = 8, end = -1; i != end; --i)
    {
      EXPECT_EQ(*itr, i);
      ++itr;
    }
}

int
main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
