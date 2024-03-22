#ifndef __DOUBLY_LINKED_LIST_HPP__
#define __DOUBLY_LINKED_LIST_HPP__

#include <iterator>
#include <memory>
#include <utility>

namespace dsa
{
struct Dbl_linked_list_node_base
{
  Dbl_linked_list_node_base* m_next;
  Dbl_linked_list_node_base* m_prev;

  Dbl_linked_list_node_base(Dbl_linked_list_node_base* prev, Dbl_linked_list_node_base* next) noexcept
      : m_prev(prev), m_next(next){};
};

template <typename Tp> struct Dbl_linked_list_node : public Dbl_linked_list_node_base
{
  Tp m_value;

  template <typename... Args>
  Dbl_linked_list_node(Args&&... args) noexcept : Dbl_linked_list_node_base(), m_value(std::forward<Args>(args)...){};
};

template <typename Tp> class Dbl_linked_list_iterator
{
public:
  typedef Tp value_type;
  typedef Tp* pointer;
  typedef Tp& reference;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef std::ptrdiff_t difference_type;

  Dbl_linked_list_iterator() : m_node(nullptr){};

  Dbl_linked_list_iterator(Dbl_linked_list_node_base* node) noexcept : m_node(node){};

  reference
  operator*() noexcept
  {
    return static_cast<Dbl_linked_list_node<Tp>*>(m_node)->m_value;
  }

  pointer
  operator->() noexcept
  {
    return std::addressof(static_cast<Dbl_linked_list_node<Tp>*>(m_node)->m_value);
  }

  Dbl_linked_list_iterator
  operator++() const noexcept
  {
    Dbl_linked_list_iterator tmp__(*this);
    m_node = m_node->m_next;
    return tmp__;
  }

  Dbl_linked_list_iterator&
  operator++(int) const noexcept
  {
    m_node = m_node->m_next;
    return *this;
  }

  Dbl_linked_list_iterator
  operator--() const noexcept
  {
    Dbl_linked_list_iterator tmp__(*this);
    m_node = m_node->m_prev;
    return tmp__;
  }

  Dbl_linked_list_iterator&
  operator--(int) const noexcept
  {
    m_node = m_node->m_prev;
    return *this;
  }

private:
  Dbl_linked_list_node_base* m_node;
};

template <typename Tp> class Dbl_linked_list_const_iterator
{
public:
  typedef Tp value_type;
  typedef const Tp* pointer;
  typedef const Tp& reference;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef std::ptrdiff_t difference_type;

  Dbl_linked_list_const_iterator() : m_node(nullptr){};

  Dbl_linked_list_const_iterator(Dbl_linked_list_node_base* node) noexcept : m_node(node){};

  Dbl_linked_list_const_iterator(const Dbl_linked_list_iterator<Tp>& itr) noexcept : m_node(itr.m_node){};

  reference
  operator*() const noexcept
  {
    return static_cast<Dbl_linked_list_node<Tp>*>(m_node)->m_value;
  }

  pointer
  operator->() const noexcept
  {
    return std::addressof(static_cast<Dbl_linked_list_node<Tp>*>(m_node)->m_value);
  }

  Dbl_linked_list_const_iterator
  operator++() const noexcept
  {
    Dbl_linked_list_const_iterator tmp__(*this);
    m_node = m_node->m_next;
    return tmp__;
  }

  Dbl_linked_list_const_iterator&
  operator++(int) const noexcept
  {
    m_node = m_node->m_next;
    return *this;
  }

  Dbl_linked_list_const_iterator
  operator--() const noexcept
  {
    Dbl_linked_list_const_iterator tmp__(*this);
    m_node = m_node->m_prev;
    return tmp__;
  }

  Dbl_linked_list_const_iterator&
  operator--(int) const noexcept
  {
    m_node = m_node->m_prev;
    return *this;
  }

private:
  Dbl_linked_list_node_base* m_node;
};

template <typename Tp, typename Alloc = std::allocator<Tp>> class Doubly_linked_list
{
  static_assert(std::is_same<std::remove_cv<Tp>, Tp>::value,
                "sda::Doubly_linked_list must have a non-const, non-volatile value_type");

  static_assert(std::is_same<typename Alloc::value_type, Tp>::value,
                "sda::Doubly_linked_list must have the same value_type as its allocator");

private:
  template <typename Itr>
  using Requires_input_itr = std::enable_if<std::is_convertible_v<typename Itr::iterator_tag, std::input_iterator_tag>>;

  typedef Dbl_linked_list_node_base<Tp> node_base;
  typedef Dbl_linked_list_node<Tp> node;
  typedef typename std::allocator_traits<Alloc>::rebind_alloc<node> alloc_node;
  typedef std::allocator_traits<alloc_node> alloc_traits;

public:
  typedef Tp value_type;
  typedef Alloc allocator_type;
  typedef Tp& reference;
  typedef const Tp& const_reference;
  typedef Dbl_linked_list_iterator<Tp> iterator;
  typedef Dbl_linked_list_const_iterator<Tp> const_iterator;
  typedef std::ptrdiff_t difference_type;
  typedef std::size_t size_type;

private:
  std::size_t m_size;
  Dbl_linked_list_node_base m_head;
};

}

#endif