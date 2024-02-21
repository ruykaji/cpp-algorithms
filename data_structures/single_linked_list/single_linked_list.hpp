#ifndef __SINGLE_LINKED_LIST_HPP__
#define __SINGLE_LINKED_LIST_HPP__

#include <memory>
#include <stdexcept>

namespace dsa
{

struct Sgl_linked_list_node_base
{
  Sgl_linked_list_node_base() : m_ptr_next(nullptr){};

  Sgl_linked_list_node_base* m_ptr_next;
};

template <typename Tp> struct Sgl_linked_list_node : public Sgl_linked_list_node_base
{
  Sgl_linked_list_node() : Sgl_linked_list_node_base(), m_value(nullptr){};

  template <typename... Args>
  Sgl_linked_list_node(Args&&... t_args) : Sgl_linked_list_node_base(), m_value(std::forward<Args>(t_args)...){};

  Tp m_value;
};

template <typename Tp> class Sgl_linked_list_iterator
{
public:
  using value_type = Tp;
  using pointer = Tp*;
  using reference = Tp&;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;

  Sgl_linked_list_iterator() : m_ptr(nullptr){};

  explicit Sgl_linked_list_iterator(Sgl_linked_list_node_base* t_ptr) noexcept : m_ptr(t_ptr){};

  reference
  operator*() const noexcept
  {
    return static_cast<Sgl_linked_list_node<Tp>*>(m_ptr)->m_value;
  };

  pointer
  operator->() const noexcept
  {
    return std::addressof(static_cast<Sgl_linked_list_node<Tp>*>(m_ptr)->m_value);
  };

  Sgl_linked_list_iterator&
  operator++() noexcept
  {
    m_ptr = m_ptr->m_ptr_next;
    return *this;
  };

  Sgl_linked_list_iterator
  operator++(int) noexcept
  {
    Sgl_linked_list_iterator tmp = *this;
    ++(*this);
    return tmp;
  };

  friend bool
  operator==(const Sgl_linked_list_iterator& t_lhs, const Sgl_linked_list_iterator& t_rhs) noexcept
  {
    return t_lhs.m_ptr == t_rhs.m_ptr;
  };

  friend bool
  operator!=(const Sgl_linked_list_iterator& t_lhs, const Sgl_linked_list_iterator& t_rhs) noexcept
  {
    return t_lhs.m_ptr != t_rhs.m_ptr;
  };

  Sgl_linked_list_node_base* m_ptr;
};

template <typename Tp> class Sgl_linked_list_const_iterator
{
public:
  using value_type = Tp;
  using pointer = const Tp*;
  using reference = const Tp&;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;

  Sgl_linked_list_const_iterator() : m_ptr(nullptr){};

  explicit Sgl_linked_list_const_iterator(Sgl_linked_list_node_base* t_ptr) noexcept : m_ptr(t_ptr){};

  Sgl_linked_list_const_iterator(const Sgl_linked_list_iterator<Tp>& t_itr) : m_ptr(t_itr.m_ptr){};

  reference
  operator*() const noexcept
  {
    return static_cast<const Sgl_linked_list_node<Tp>*>(m_ptr)->m_value;
  };

  pointer
  operator->() const noexcept
  {
    return std::addressof(static_cast<const Sgl_linked_list_node<Tp*>>(m_ptr)->m_value);
  };

  Sgl_linked_list_const_iterator&
  operator++() noexcept
  {
    m_ptr = m_ptr->m_ptr_next;
    return *this;
  };

  Sgl_linked_list_const_iterator
  operator++(int) noexcept
  {
    Sgl_linked_list_const_iterator tmp = *this;
    ++(*this);
    return tmp;
  };

  const Sgl_linked_list_node_base* m_ptr;
};

template <typename Tp>
bool
operator==(const Sgl_linked_list_iterator<Tp>& t_lhs, const Sgl_linked_list_const_iterator<Tp>& t_rhs) noexcept
{
  return t_lhs.m_ptr == t_rhs.m_ptr;
};

template <typename Tp>
bool
operator!=(const Sgl_linked_list_iterator<Tp>& t_lhs, const Sgl_linked_list_const_iterator<Tp>& t_rhs) noexcept
{
  return t_lhs.m_ptr != t_rhs.m_ptr;
};

template <typename Tp, typename Alloc = std::allocator<Tp>> class Single_linked_list
{

  static_assert(std::is_same<typename std::remove_cv<Tp>::type, Tp>::value,
                "sda::Single_linked_list must have a non-const, non-volatile value_type");

  static_assert(std::is_same<typename Alloc::value_type, Tp>::value,
                "sda::Single_linked_list must have the same value_type as its allocator");

private:
  typedef Sgl_linked_list_node_base node_base;
  typedef Sgl_linked_list_node<Tp> node;
  typedef typename std::allocator_traits<Alloc>::rebind_alloc<node> node_alloc;
  typedef std::allocator_traits<node_alloc> alloc_traits;

public:
  typedef Tp value_type;
  typedef Tp& reference;
  typedef const Tp& const_reference;
  typedef Sgl_linked_list_iterator<Tp> iterator;
  typedef Sgl_linked_list_const_iterator<Tp> const_iterator;
  typedef std::ptrdiff_t difference_type;
  typedef std::size_t size_type;

  explicit Single_linked_list(const Alloc& t_alloc = Alloc()) noexcept : m_size(0), m_head(), m_alloc(t_alloc){};

  explicit Single_linked_list(std::size_t t_size, const Alloc& t_alloc = Alloc())
      : m_size(0), m_head(), m_alloc(t_alloc)
  {
    node_base* to = &m_head;

    for(; t_size; --t_size)
      {
        to->m_ptr_next = m_create_node();
        to = to->m_ptr_next;
      }
  };

  explicit Single_linked_list(std::size_t t_size, const Tp& t_value, const Alloc& t_alloc = Alloc())
      : m_size(0), m_head(), m_alloc(t_alloc)
  {
    node_base* to = &m_head;

    for(; t_size; --t_size)
      {
        to->m_ptr_next = m_create_node(t_value);
        to = to->m_ptr_next;
      }
  };

  iterator
  before_begin() noexcept
  {
    return iterator(&m_head);
  }

  const_iterator
  before_begin() const noexcept
  {
    return const_iterator(&m_head);
  }

  iterator
  begin() noexcept
  {
    return iterator(m_head.m_ptr_next);
  };

  const_iterator
  begin() const noexcept
  {
    return const_iterator(m_head.m_ptr_next);
  };

  iterator
  end() noexcept
  {
    return iterator(nullptr);
  };

  const_iterator
  end() const noexcept
  {
    return const_iterator(nullptr);
  };

  const_iterator
  cbefore_begin() noexcept
  {
    return const_iterator(&m_head);
  }

  const_iterator
  cbegin() const noexcept
  {
    return const_iterator(m_head.m_ptr_next);
  };

  const_iterator
  cend() const noexcept
  {
    return const_iterator(nullptr);
  };

  void
  push_front(const Tp& t_value) noexcept
  {
    m_insert_after(cbefore_begin(), t_value);
  }

  void
  push_front(Tp&& t_value)
  {
    m_insert_after(cbefore_begin(), std::move(t_value));
  }

  template <typename... Args>
  void
  emplace_front(Args&&... t_args)
  {
    m_insert_after(cbefore_begin(), std::forward<Args>(t_args)...);
  }

  iterator
  insert_after(const_iterator t_pos, const Tp& t_value)
  {
    return m_insert_after(t_pos, t_value);
  }

  iterator
  insert_after(const_iterator t_pos, Tp&& t_value)
  {
    return m_insert_after(t_pos, std::move(t_value));
  }

  template <typename... Args>
  iterator
  emplace_after(const_iterator t_pos, Args&&... t_args)
  {
    return m_insert_after(t_pos, std::forward<Args>(t_args)...);
  }

  /**
   * @brief Returns read/write reference to the data at the first element
   * of the Single_linked_list
   *
   * @return Tp&
   */
  reference
  front() noexcept
  {
    return std::addressof(static_cast<node*>(&m_head.m_ptr_next)->m_value);
  }

  /**
   * @brief Returns read-only(constant) reference to the data at the first
   * element of the Single_linked_list
   *
   * @return const Tp&
   */
  const_reference
  front() const noexcept
  {
    return std::addressof(static_cast<node*>(&m_head.m_ptr_next)->m_value);
  }

  iterator
  erase_after(const_iterator t_pos)
  {
    node_base* to = static_cast<node_base*>(t_pos.m_ptr);
    node* curr = static_cast<node*>(to->m_ptr_next);

    to->m_ptr_next = curr->m_ptr_next;

    alloc_traits::destroy(m_alloc, curr);
    alloc_traits::deallocate(m_alloc, curr, 1);

    return iterator(to->m_ptr_next);
  }

  iterator
  erase_after(const_iterator t_pos, const_iterator t_last)
  {
    node_base* from = static_cast<node_base*>(t_pos.m_ptr);

    while(from->m_ptr_next != t_last.m_ptr)
      {
        node* curr = static_cast<node*>(from->m_ptr_next);

        from->m_ptr_next = curr->m_ptr_next;

        alloc_traits::destroy(m_alloc, curr);
        alloc_traits::deallocate(m_alloc, curr, 1);

        from = from->m_ptr_next;
      }

    return iterator(from->m_ptr_next);
  }

  void
  remove(const Tp& t_value)
  {
    node_base* curr = &m_head;
    node_base* extra = nullptr;

    while(node* tmp = static_cast<node*>(curr->m_ptr_next))
      {
        if(tmp->m_value == t_value)
          {
            if(std::addressof(t_value) != std::addressof(tmp->m_value))
              {
                erase_after(curr);
                continue;
              }
            else
              extra = curr;
          }

        curr = curr->m_ptr_next;
      }

    if(!extra)
      erase_after(extra);
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
  template <typename... Args>
  node*
  m_create_node(Args&&... t_args)
  {
    node* thing = alloc_traits::allocate(m_alloc, 1);

    try
      {
        alloc_traits::construct(m_alloc, thing, std::forward<Args>(t_args)...);
      }
    catch(...)
      {
        alloc_traits::deallocate(m_alloc, thing, 1);
        throw;
      }

    return thing;
  }

  template <typename... Args>
  iterator
  m_insert_after(const_iterator t_pos, Args&&... t_args)
  {
    node_base* to = const_cast<node_base*>(t_pos.m_ptr);
    node* thing = m_create_node(std::forward<Args>(t_args)...);

    thing->m_ptr_next = to->m_ptr_next;
    to->m_ptr_next = thing;
    ++m_size;
    return iterator(to->m_ptr_next);
  }

protected:
  std::size_t m_size;
  node_base m_head;
  node_alloc m_alloc;
};

}

#endif