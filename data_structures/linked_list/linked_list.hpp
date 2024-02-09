#ifndef __LINKED_LIST_HPP__
#define __LINKED_LIST_HPP__

#include <iterator>
#include <memory>
#include <stdexcept>

namespace my_std
{
template <typename value_type> class LinkedList
{
  struct Node
  {
    std::shared_ptr<Node> ptr_next;
    std::unique_ptr<value_type> value;

    Node() noexcept : ptr_next(nullptr), value(nullptr){};

    Node(std::shared_ptr<Node> t_ptr_next, const value_type& t_value) noexcept
        : ptr_next(t_ptr_next),
          value(std::make_unique<value_type>(t_value)){};

    template <typename... Args>
    Node(std::shared_ptr<Node> t_ptr_next, Args&&... t_args)
        : ptr_next(t_ptr_next), value(std::make_unique<value_type>(std::forward<Args>(t_args)...)){};
  };

  using node = Node;
  using const_node = const Node;

public:
  template <typename pointer_type> class Iterator
  {
  public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using type = value_type;
    using pointer = value_type*;
    using reference = value_type&;

    Iterator(std::shared_ptr<pointer_type> t_ptr) noexcept : m_ptr(t_ptr){};

    reference
    operator*() const& noexcept
    {
      return *m_ptr->value;
    };

    pointer
    operator->() const noexcept
    {
      return *m_ptr->value;
    };

    Iterator&
    operator++() &
    {
      if(!m_ptr->ptr_next)
        {
          throw std::out_of_range("Attempt to go out of range.");
        }

      m_ptr = m_ptr->ptr_next;
      return *this;
    };

    Iterator
    operator++(int)
    {
      if(!m_ptr->ptr_next)
        {
          throw std::out_of_range("Attempt to go out of range.");
        }

      Iterator tmp = *this;
      ++(*this);
      return tmp;
    };

    friend bool
    operator==(const Iterator& t_lhs, const Iterator& t_rhs)
    {
      return t_lhs.m_ptr == t_rhs.m_ptr;
    };

    friend bool
    operator!=(const Iterator& t_lhs, const Iterator& t_rhs)
    {
      return t_lhs.m_ptr != t_rhs.m_ptr;
    };

  private:
    std::shared_ptr<pointer_type> m_ptr;
  };

  using iterator = Iterator<node>;
  using const_iterator = Iterator<const_node>;

  LinkedList() : m_size(0), m_ptr_end(std::make_shared<node>()), m_ptr_head(m_ptr_end), m_ptr_tail(m_ptr_end){};

  iterator
  begin()
  {
    return iterator{ m_ptr_head };
  };

  iterator
  end()
  {
    return iterator{ m_ptr_end };
  };

  const_iterator
  cbegin()
  {
    return const_iterator{ m_ptr_head };
  };

  const_iterator
  cend()
  {
    return const_iterator{ m_ptr_end };
  };

  void
  push_back(const value_type& t_value) noexcept
  {
    std::shared_ptr<node> ptr_node = std::make_shared<node>(m_ptr_end, t_value);

    if(m_size == 0)
      {
        m_ptr_head = ptr_node;
      }
    else
      {
        m_ptr_tail->ptr_next = ptr_node;
      }

    m_ptr_tail = ptr_node;
    ++m_size;
  };

  void
  push_back(value_type&& t_value) noexcept
  {
    emplace_back(std::move(t_value));
  };

  template <typename... Args>
  void
  emplace_back(Args&&... t_args) noexcept
  {
    std::shared_ptr<node> ptr_node = std::make_shared<node>(m_ptr_end, std::forward<Args>(t_args)...);

    if(m_size == 0)
      {
        m_ptr_head = ptr_node;
      }
    else
      {
        m_ptr_tail->ptr_next = ptr_node;
      }

    m_ptr_tail = ptr_node;
    ++m_size;
  }

  void
  insert(const_iterator t_itr, const value_type& t_value)
  {
    if(t_itr.m_ptr == m_ptr_end)
      {
        push_back(t_value);
      }
    else if(t_itr.m_ptr == m_ptr_head)
      {
      }
  }

  std::size_t
  size() const noexcept
  {
    return m_size;
  };

  bool
  empty() const noexcept
  {
    return m_size == 0;
  };

private:
  std::size_t m_size;
  std::shared_ptr<node> m_ptr_end;
  std::shared_ptr<node> m_ptr_head;
  std::shared_ptr<node> m_ptr_tail;
};
}

#endif