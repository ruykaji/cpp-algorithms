#include <initializer_list>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "single_linked_list.hpp"

template <typename Tp> class Typed_single_linked_list_fixture : public ::testing::Test
{
public:
  using List = dsa::Single_linked_list<Tp>;

  void
  compare_size(const List& list, List::size_type size)
  {
    EXPECT_EQ(list.size(), size);
  }

  template <typename Up>
  void
  compare_with_value(const List& list, const Up& value)
  {
    for(auto list_itr__ = std::cbegin(list), list_end__ = std::cend(list); list_itr__ != list_end__; ++list_itr__)
      {
        if(*list_itr__ != value)
          FAIL();
      }
  };

  template <typename Rhs_container>
  void
  compare_containers(const List& list, const Rhs_container& rhs)
  {
    EXPECT_EQ(std::distance(std::cbegin(list), std::cend(list)), std::distance(std::cbegin(rhs), std::cend(rhs)));

    auto list_itr__ = std::cbegin(list);

    for(auto rhs_itr__ = std::cbegin(rhs), rhs_end__ = std::cend(rhs); rhs_itr__ != rhs_end__;
        ++list_itr__, ++rhs_itr__)
      {
        if(*list_itr__ != *rhs_itr__)
          FAIL();
      }
  };

protected:
  static Tp s_default_value;
  static std::initializer_list<Tp> s_list_a;
  static std::initializer_list<Tp> s_list_b;
};

using Value_types = ::testing::Types<int, std::string>;
TYPED_TEST_SUITE(Typed_single_linked_list_fixture, Value_types);

// Some shortcut names
template <typename Tp> using Init_list = std::initializer_list<Tp>;
template <typename Tp> using Tsllf = Typed_single_linked_list_fixture<Tp>;

// int specialization
template <> int Tsllf<int>::s_default_value = 11;
template <> Init_list<int> Tsllf<int>::s_list_a{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
template <> Init_list<int> Tsllf<int>::s_list_b{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

// std::string specialization
template <> std::string Tsllf<std::string>::s_default_value = "k";
template <> Init_list<std::string> Tsllf<std::string>::s_list_a{ "a", "b", "c", "d", "e", "f", "g", "h", "i", "j" };
template <> Init_list<std::string> Tsllf<std::string>::s_list_b{ "j", "i", "h", "g", "f", "e", "d", "c", "b", "a" };

TYPED_TEST(Typed_single_linked_list_fixture, Sized_default_value_constructor)
{
  typename TestFixture::List list__(10);

  TestFixture::compare_size(list__, 10);
  TestFixture::compare_with_value(list__, typename TestFixture::List::value_type());
}

TYPED_TEST(Typed_single_linked_list_fixture, Sized_provided_value_constructor)
{
  typename TestFixture::List list__(10, TestFixture::s_default_value);

  TestFixture::compare_size(list__, 10);
  TestFixture::compare_with_value(list__, TestFixture::s_default_value);
}

TYPED_TEST(Typed_single_linked_list_fixture, Initializer_list_constructor)
{
  typename TestFixture::List list__(TestFixture::s_list_a);

  TestFixture::compare_containers(list__, TestFixture::s_list_a);
}

TYPED_TEST(Typed_single_linked_list_fixture, Iterator_constructor)
{
  std::vector<typename TestFixture::List::value_type> vec__(TestFixture::s_list_a);
  typename TestFixture::List list__(vec__.begin(), vec__.end());

  TestFixture::compare_containers(list__, vec__);
}

TYPED_TEST(Typed_single_linked_list_fixture, Copy_constructor)
{
  typename TestFixture::List list_a__(TestFixture::s_list_a);
  typename TestFixture::List list_b__(list_a__);

  TestFixture::compare_containers(list_a__, list_b__);
}

TYPED_TEST(Typed_single_linked_list_fixture, Copy_constructor_on_empty_list)
{
  typename TestFixture::List list_a__{};
  typename TestFixture::List list_b__(list_a__);

  TestFixture::compare_containers(list_a__, list_b__);
}

TYPED_TEST(Typed_single_linked_list_fixture, Move_constructor)
{
  typename TestFixture::List list_a__(TestFixture::s_list_a);
  typename TestFixture::List list_b__(std::move(list_a__));

  TestFixture::compare_size(list_a__, 0);
  TestFixture::compare_containers(list_b__, TestFixture::s_list_a);
}

TYPED_TEST(Typed_single_linked_list_fixture, Move_constructor_on_empty_list)
{
  typename TestFixture::List list_a__{};
  typename TestFixture::List list_b__(std::move(list_a__));

  TestFixture::compare_size(list_a__, 0);
  TestFixture::compare_containers(list_b__, list_a__);
}

TYPED_TEST(Typed_single_linked_list_fixture, Initializer_list_assignment_less_size)
{
  typename TestFixture::List list__(TestFixture::s_list_a);

  list__.erase_after(list__.before_begin());
  list__ = TestFixture::s_list_b;

  TestFixture::compare_containers(list__, TestFixture::s_list_b);
}

TYPED_TEST(Typed_single_linked_list_fixture, Initializer_list_assignment_bigger_size)
{
  typename TestFixture::List list__(TestFixture::s_list_a);

  list__.insert_after(list__.before_begin(), TestFixture::s_default_value);
  list__ = TestFixture::s_list_b;

  TestFixture::compare_containers(list__, TestFixture::s_list_b);
}

TYPED_TEST(Typed_single_linked_list_fixture, Copy_assignment)
{
  typename TestFixture::List list_a__(TestFixture::s_list_a);
  typename TestFixture::List list_b__(TestFixture::s_list_b);

  list_a__ = list_b__;

  TestFixture::compare_containers(list_a__, TestFixture::s_list_b);
}

TYPED_TEST(Typed_single_linked_list_fixture, Copy_assignment_of_empty_list)
{
  typename TestFixture::List list_a__(TestFixture::s_list_a);
  typename TestFixture::List list_b__{};

  list_a__ = list_b__;

  TestFixture::compare_containers(list_a__, list_b__);
}

TYPED_TEST(Typed_single_linked_list_fixture, Move_assignment)
{
  typename TestFixture::List list_a__(TestFixture::s_list_a);
  typename TestFixture::List list_b__(TestFixture::s_list_b);

  list_a__ = std::move(list_b__);

  TestFixture::compare_containers(list_a__, TestFixture::s_list_b);
}

TYPED_TEST(Typed_single_linked_list_fixture, Move_assignment_of_empty_list)
{
  typename TestFixture::List list_a__(TestFixture::s_list_a);
  typename TestFixture::List list_b__{};

  list_a__ = std::move(list_b__);

  TestFixture::compare_containers(list_a__, list_b__);
}

TYPED_TEST(Typed_single_linked_list_fixture, Insert_a_lvalue)
{
  typename TestFixture::List list__(TestFixture::s_list_a);

  list__.insert_after(list__.before_begin(), TestFixture::s_default_value);
  EXPECT_EQ(*list__.begin(), TestFixture::s_default_value);
}

TYPED_TEST(Typed_single_linked_list_fixture, Insert_an_amount_of_values)
{
  typename TestFixture::List list__;

  list__.insert_after(list__.before_begin(), 10, TestFixture::s_default_value);

  for(auto value : list__)
    {
      if(value != TestFixture::s_default_value)
        FAIL();
    }
}

TYPED_TEST(Typed_single_linked_list_fixture, Insert_a_container)
{
  typename TestFixture::List list__;
  std::vector<typename TestFixture::List::value_type> vec__(TestFixture::s_list_a);

  list__.insert_after(list__.before_begin(), vec__.begin(), vec__.end());

  TestFixture::compare_containers(list__, vec__);
}

TYPED_TEST(Typed_single_linked_list_fixture, Erase_a_value)
{
  typename TestFixture::List list__(TestFixture::s_list_a);
  std::vector<typename TestFixture::List::value_type> vec__(TestFixture::s_list_a);

  vec__.erase(vec__.begin());
  list__.erase_after(list__.before_begin());

  TestFixture::compare_containers(list__, vec__);
}

TYPED_TEST(Typed_single_linked_list_fixture, Erase_a_range_of_values)
{
  typename TestFixture::List list__(TestFixture::s_list_a);
  std::vector<typename TestFixture::List::value_type> vec__(TestFixture::s_list_a);

  auto list_list__ = list__.begin();
  auto vec_list__ = vec__.begin();

  std::advance(list_list__, 3);
  std::advance(vec_list__, 3);

  vec__.erase(vec__.begin(), vec_list__);
  list__.erase_after(list__.before_begin(), list_list__);

  TestFixture::compare_containers(list__, vec__);
}

TYPED_TEST(Typed_single_linked_list_fixture, Splice_lvalue_list)
{
  typename TestFixture::List list_a__;
  typename TestFixture::List list_b__(TestFixture::s_list_b);

  list_a__.splice_after(list_a__.before_begin(), list_b__);

  EXPECT_TRUE(list_b__.empty());

  TestFixture::compare_containers(list_a__, TestFixture::s_list_b);
}

TYPED_TEST(Typed_single_linked_list_fixture, Splice_rvalue_list)
{
  typename TestFixture::List list_a__;

  list_a__.splice_after(list_a__.before_begin(), typename TestFixture::List(TestFixture::s_list_b));

  TestFixture::compare_containers(list_a__, TestFixture::s_list_b);
}

TYPED_TEST(Typed_single_linked_list_fixture, Splice_within_a_range)
{
  typename TestFixture::List list_a__;
  typename TestFixture::List list_b__(TestFixture::s_list_b);

  list_a__.splice_after(list_a__.before_begin(), list_b__.before_begin(), list_b__.end());

  EXPECT_TRUE(list_b__.empty());

  TestFixture::compare_containers(list_a__, TestFixture::s_list_b);
}

int
main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
