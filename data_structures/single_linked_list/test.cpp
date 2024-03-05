#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "single_linked_list.hpp"

TEST(SingleLinkedListContainer, Default_Constructor)
{
  dsa::Single_linked_list<int> list;

  EXPECT_TRUE(list.empty());
}

TEST(SingleLinkedListContainer, Initial_Size_Construction)
{
  dsa::Single_linked_list<int> list(10);

  EXPECT_EQ(list.size(), 10);
}

TEST(SingleLinkedListContainer, Initial_Size_And_Value_Construction)
{
  dsa::Single_linked_list<int> list(10, 1);

  for(auto value : list)
    EXPECT_EQ(value, 1);
}

TEST(SingleLinkedListContainer, Iterator_Constructor)
{
  std::vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  dsa::Single_linked_list<int> list(vec.begin(), vec.end());

  EXPECT_EQ(list.size(), vec.size());

  std::size_t i = 0;

  for(auto value : list)
    {
      EXPECT_EQ(value, vec[i]);
      ++i;
    }
}

TEST(SingleLinkedListContainer, Initialization_List_Constructor)
{
  dsa::Single_linked_list<int> list{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  EXPECT_EQ(list.size(), 10);

  std::size_t i = 0;

  for(auto value : list)
    {
      EXPECT_EQ(value, i);
      ++i;
    }
}

TEST(SingleLinkedListContainer, Copy_Constructor)
{
  dsa::Single_linked_list<int> list_a{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  dsa::Single_linked_list<int> list_b(list_a);

  EXPECT_EQ(list_b.size(), 10);

  for(auto itr_a = list_a.begin(), itr_b = list_b.begin(), end = list_a.end(); itr_a != end; ++itr_a, ++itr_b)
    {
      EXPECT_EQ(*itr_a, *itr_b);
      EXPECT_NE(&*itr_a, &*itr_b);
    }
}

TEST(SingleLinkedListContainer, Move_Constructor)
{
  dsa::Single_linked_list<int> list_a{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  dsa::Single_linked_list<int> list_b(std::move(list_a));

  EXPECT_EQ(list_a.size(), 0);
  EXPECT_EQ(list_b.size(), 10);

  std::size_t i = 0;

  for(auto value : list_b)
    {
      EXPECT_EQ(value, i);
      ++i;
    }
}

int
main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
