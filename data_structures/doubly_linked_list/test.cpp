#include <initializer_list>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "doubly_linked_list.hpp"

template <typename Tp> class Typed_doubly_linked_list_fixture : public ::testing::Test
{
public:
  using List = dsa::Doubly_linked_list<Tp>;

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
TYPED_TEST_SUITE(Typed_doubly_linked_list_fixture, Value_types);

// Some shortcut names
template <typename Tp> using Init_list = std::initializer_list<Tp>;
template <typename Tp> using Tbllf = Typed_doubly_linked_list_fixture<Tp>;

// int specialization
template <> int Tbllf<int>::s_default_value = 5;
template <> Init_list<int> Tbllf<int>::s_list_a{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
template <> Init_list<int> Tbllf<int>::s_list_b{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

// std::string specialization
template <> std::string Tbllf<std::string>::s_default_value = "e";
template <> Init_list<std::string> Tbllf<std::string>::s_list_a{ "a", "b", "c", "d", "e", "f", "g", "h", "i", "j" };
template <> Init_list<std::string> Tbllf<std::string>::s_list_b{ "j", "i", "h", "g", "f", "e", "d", "c", "b", "a" };

TYPED_TEST(Typed_doubly_linked_list_fixture, Sized_default_value_constructor)
{
  typename TestFixture::List list__(10);

  TestFixture::compare_size(list__, 10);
  TestFixture::compare_with_value(list__, typename TestFixture::List::value_type());
}

TYPED_TEST(Typed_doubly_linked_list_fixture, Sized_provided_value_constructor)
{
  typename TestFixture::List list__(10, TestFixture::s_default_value);

  TestFixture::compare_size(list__, 10);
  TestFixture::compare_with_value(list__, TestFixture::s_default_value);
}

TYPED_TEST(Typed_doubly_linked_list_fixture, Initializer_list_constructor)
{
  typename TestFixture::List list__(TestFixture::s_list_a);

  TestFixture::compare_containers(list__, TestFixture::s_list_a);
}

TYPED_TEST(Typed_doubly_linked_list_fixture, Iterator_constructor)
{
  std::vector<typename TestFixture::List::value_type> vec__(TestFixture::s_list_a);
  typename TestFixture::List list__(vec__.begin(), vec__.end());

  TestFixture::compare_containers(list__, vec__);
}

TYPED_TEST(Typed_doubly_linked_list_fixture, Copy_constructor)
{
  typename TestFixture::List list_a__(TestFixture::s_list_a);
  typename TestFixture::List list_b__(list_a__);

  TestFixture::compare_containers(list_a__, list_b__);
}

TYPED_TEST(Typed_doubly_linked_list_fixture, Move_constructor)
{
  typename TestFixture::List list_a__(TestFixture::s_list_a);
  typename TestFixture::List list_b__(std::move(list_a__));

  TestFixture::compare_size(list_a__, 0);
  TestFixture::compare_containers(list_b__, TestFixture::s_list_a);
}
TYPED_TEST(Typed_doubly_linked_list_fixture, Initializer_list_assignment)
{
  typename TestFixture::List list__(TestFixture::s_list_a);

  list__ = TestFixture::s_list_b;

  TestFixture::compare_containers(list__, TestFixture::s_list_b);
}

int
main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
