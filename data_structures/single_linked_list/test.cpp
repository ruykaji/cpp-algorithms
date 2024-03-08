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

  EXPECT_EQ(list.size(), 10);

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

  EXPECT_EQ(list_a.size(), 10);
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

TEST(SingleLinkedListContainer, Initialization_List_Assignment)
{
  dsa::Single_linked_list<int> list;

  list = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  EXPECT_EQ(list.size(), 10);

  std::size_t i = 0;

  for(auto value : list)
    {
      EXPECT_EQ(value, i);
      ++i;
    }
}

TEST(SingleLinkedListContainer, Copy_Assignment)
{
  dsa::Single_linked_list<int> list_a{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  dsa::Single_linked_list<int> list_b;

  list_b = list_a;

  EXPECT_EQ(list_a.size(), 10);
  EXPECT_EQ(list_b.size(), 10);

  for(auto itr_a = list_a.begin(), itr_b = list_b.begin(), end = list_a.end(); itr_a != end; ++itr_a, ++itr_b)
    {
      EXPECT_EQ(*itr_a, *itr_b);
      EXPECT_NE(&*itr_a, &*itr_b);
    }
}

TEST(SingleLinkedListContainer, Move_Assignment)
{
  dsa::Single_linked_list<int> list_a{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  dsa::Single_linked_list<int> list_b;

  list_b = std::move(list_a);

  EXPECT_TRUE(list_a.empty());
  EXPECT_EQ(list_b.size(), 10);

  std::size_t i = 0;

  for(auto value : list_b)
    {
      EXPECT_EQ(value, i);
      ++i;
    }
}

TEST(SingleLinkedListContainer, Splice_Move)
{
  dsa::Single_linked_list<int> list_a{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
  dsa::Single_linked_list<int> list_b{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  list_b.splice_after(list_b.cbefore_begin(), std::move(list_a));

  EXPECT_TRUE(list_a.empty());

  auto itr_b = ++list_b.cbefore_begin();

  EXPECT_EQ(list_b.size(), 20);

  for(int32_t i = 9; i > -1; --i)
    {
      EXPECT_EQ(*itr_b, i);
      ++itr_b;
    }

  for(int32_t i = 0; i < 10; ++i)
    {
      EXPECT_EQ(*itr_b, i);
      ++itr_b;
    }
}

TEST(SingleLinkedListContainer, Splice_Two_Iterators)
{
  dsa::Single_linked_list<int> list_a{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
  dsa::Single_linked_list<int> list_b{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  list_b.splice_after(list_b.cbefore_begin(), list_a.cbefore_begin(), list_a.cend());

  EXPECT_TRUE(list_a.empty());

  auto itr_b = ++list_b.cbefore_begin();

  EXPECT_EQ(list_b.size(), 20);

  for(int32_t i = 9; i > -1; --i)
    {
      EXPECT_EQ(*itr_b, i);
      ++itr_b;
    }

  for(int32_t i = 0; i < 10; ++i)
    {
      EXPECT_EQ(*itr_b, i);
      ++itr_b;
    }
}



int
main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
