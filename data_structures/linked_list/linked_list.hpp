#ifndef __LINKED_LIST_HPP__
#define __LINKED_LIST_HPP__

#include <iterator>
#include <memory>
#include <stdexcept>

namespace linked_list
{
template <typename Tp>
class Node
{
  using sptr_node_t = std::shared_ptr<Node<Tp> >;
  using uptr_value_t = std::unique_ptr<Tp>;

public:
  Node() noexcept : m_ptr_next(nullptr), value(nullptr){};

  Node(sptr_node_t t_ptr_next, const Tp& t_value) noexcept
      : m_ptr_next(t_ptr_next),
        value(std::make_unique<Tp>(t_value)){};

  template <typename... Args>
  Node(sptr_node_t t_ptr_next, Args&&... t_args)
      : m_ptr_next(t_ptr_next), value(std::make_unique<Tp>(std::forward<Args>(t_args)...)){};

  sptr_node_t m_ptr_next;
  uptr_value_t value;
};

template <typename Tp>
class Iterator
{
  using node_t = Node<Tp>;
  using sptr_node_t = std::shared_ptr<node_t>;

public:
  using iterator_category = std::forward_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using type = Tp;
  using pointer = Tp*;
  using reference = Tp&;

  Iterator(sptr_node_t t_ptr) noexcept : m_ptr(t_ptr){};

  reference
  operator*() const noexcept
  {
    return *m_ptr->value;
  };

  pointer
  operator->() const noexcept
  {
    return *m_ptr->value;
  };

  Iterator&
  operator++() noexcept
  {
    m_ptr = m_ptr->m_ptr_next;
    return *this;
  };

  Iterator
  operator++(int) noexcept
  {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
  };

  friend bool
  operator==(const Iterator& t_lhs, const Iterator& t_rhs) noexcept
  {
    return t_lhs.m_ptr == t_rhs.m_ptr;
  };

  friend bool
  operator!=(const Iterator& t_lhs, const Iterator& t_rhs) noexcept
  {
    return t_lhs.m_ptr != t_rhs.m_ptr;
  };

  sptr_node_t m_ptr;
};

template <typename Tp>
class ConstIterator
{
  using sptr_node_t = std::shared_ptr<Node<Tp> >;

public:
  using iterator_category = std::forward_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using type = Tp;
  using pointer = const Tp*;
  using reference = const Tp&;

  ConstIterator(sptr_node_t t_ptr) noexcept : m_ptr(t_ptr){};

  reference
  operator*() const noexcept
  {
    return *m_ptr->value;
  };

  pointer
  operator->() const noexcept
  {
    return *m_ptr->value;
  };

  ConstIterator&
  operator++() noexcept
  {
    m_ptr = m_ptr->ptr_next;
    return *this;
  };

  ConstIterator
  operator++(int) noexcept
  {
    ConstIterator tmp = *this;
    ++(*this);
    return tmp;
  };

  friend bool
  operator==(const ConstIterator& t_lhs, const ConstIterator& t_rhs) noexcept
  {
    return t_lhs.m_ptr == t_rhs.m_ptr;
  };

  friend bool
  operator!=(const ConstIterator& t_lhs, const ConstIterator& t_rhs) noexcept
  {
    return t_lhs.m_ptr != t_rhs.m_ptr;
  };

  sptr_node_t m_ptr;
};
}

template <typename Tp>
class LinkedList
{
  using node_t = linked_list::Node<Tp>;
  using sptr_node_t = std::shared_ptr<node_t>;

public:
  using iterator = linked_list::Iterator<Tp>;
  using const_iterator = linked_list::ConstIterator<Tp>;

  LinkedList() : m_size(0), m_ptr_end(std::make_shared<node_t>()), m_ptr_head(m_ptr_end), m_ptr_tail(m_ptr_end){};

  iterator
  begin() noexcept
  {
    return iterator{ m_ptr_head };
  };

  iterator
  end() noexcept
  {
    return iterator{ m_ptr_end };
  };

  const_iterator
  cbegin() const noexcept
  {
    return const_iterator{ m_ptr_head };
  };

  const_iterator
  cend() const noexcept
  {
    return const_iterator{ m_ptr_end };
  };

  void
  push_back(const Tp& t_value) noexcept
  {
    sptr_node_t ptr_node = std::make_shared<node_t>(m_ptr_end, t_value);

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
  push_back(Tp&& t_value) noexcept
  {
    emplace_back(std::move(t_value));
  };

  template <typename... Args>
  void
  emplace_back(Args&&... t_args) noexcept
  {
    sptr_node_t ptr_node = std::make_shared<node_t>(m_ptr_end, std::forward<Args>(t_args)...);

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
  push_front(const Tp& t_value) noexcept
  {
    m_ptr_head = std::make_shared<node_t>(m_ptr_head, t_value);

    if(size == 0)
      {
        m_ptr_tail = m_ptr_head;
      }

    ++size;
  }

  void
  push_front(Tp&& t_value) noexcept
  {
    emplace_front(m_ptr_head, std::move(t_value));
  }

  template <typename... Args>
  void
  emplace_front(Args&&... t_args) noexcept
  {
    m_ptr_head = std::make_shared<node_t>(m_ptr_head, std::forward<Args>(t_args)...);

    if(size == 0)
      {
        m_ptr_tail = m_ptr_head;
      }

    ++size;
  }

  void
  insert(const_iterator t_itr, const Tp& t_value)
  {
    sptr_node_t ptr_node = std::make_shared<node_t>(t_itr, t_value);

    if(t_itr.m_ptr == m_ptr_head)
      {
        m_ptr_head = ptr_node;
      }
    else
      {
        for(auto &itr = begin(), itr_end = end(); itr != itr_end; ++itr)
          {
            if(itr.m_ptr->m_ptr_next == t_itr.m_ptr)
              {
                itr.m_ptr->m_ptr_next = ptr_node;
                break;
              }
          }
      }
  }

  void
  insert(const_iterator t_itr, const Tp& t_value)
  {
    sptr_node_t ptr_node = std::make_shared<node_t>(t_itr, t_value);

    if(t_itr == m_ptr_head)
      {
        m_ptr_tail = ptr_node;
      }
    else
      {
        for(auto &itr = begin(), itr_end = end(); itr != itr_end; ++itr)
          {
            if(itr.m_ptr->m_ptr_next == t_itr.m_ptr)
              {
                itr.m_ptr->m_ptr_next = ptr_node;
                break;
              }
          }
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

protected:
  std::size_t m_size;
  sptr_node_t m_ptr_end;
  sptr_node_t m_ptr_head;
  sptr_node_t m_ptr_tail;
};

#endif