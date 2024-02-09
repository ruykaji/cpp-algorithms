#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "linked_list.hpp"

TEST (LinkedListContainer, EmptyWhenEmpty)
{
  my_std::LinkedList<int> list;

  EXPECT_EQ (list.size (), 0);
  EXPECT_TRUE (list.empty ());
}

TEST (LinkedListContainer, BeginEqualEndIteratorWhenEmpty)
{
  my_std::LinkedList<int> list;

  EXPECT_EQ (list.begin (), list.end ());
  EXPECT_EQ (list.cbegin (), list.cend ());
}

TEST (LinkedListContainer, ExpectOutOfRangeThrow)
{
  my_std::LinkedList<int> list;

  {
    auto end_itr = list.end ();

    EXPECT_THROW (end_itr++, std::out_of_range);
    EXPECT_THROW (++end_itr, std::out_of_range);
  }

  {
    auto begin_itr = list.begin ();

    EXPECT_THROW (begin_itr++, std::out_of_range);
    EXPECT_THROW (++begin_itr, std::out_of_range);
  }
}

TEST (LinkedListContainer, PushBackTrivialType)
{
  my_std::LinkedList<int> list;

  for (std::size_t i = 0, end = 9; i != end; ++i)
    {
      list.push_back (i);
    }
}

int
main (int argc, char** argv)
{
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}
