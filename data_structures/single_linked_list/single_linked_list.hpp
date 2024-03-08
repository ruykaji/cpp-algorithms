#ifndef __SINGLE_LINKED_LIST_HPP__
#define __SINGLE_LINKED_LIST_HPP__

#include <memory>
#include <stdexcept>

namespace dsa
{

struct Sgl_linked_list_node_base
{
  Sgl_linked_list_node_base* m_ptr_next;

  Sgl_linked_list_node_base() noexcept : m_ptr_next(nullptr){};

  Sgl_linked_list_node_base*
  m_transfer_after(Sgl_linked_list_node_base* t_begin, Sgl_linked_list_node_base* t_end) noexcept
  {
    Sgl_linked_list_node_base* keep__ = t_begin->m_ptr_next;

    if(t_end)
      {
        t_begin->m_ptr_next = t_end->m_ptr_next;
        t_end->m_ptr_next = m_ptr_next;
      }
    else
      t_begin->m_ptr_next = nullptr;

    m_ptr_next = keep__;
    return t_end;
  }
};

template <typename Tp> struct Sgl_linked_list_node : public Sgl_linked_list_node_base
{
  Tp m_value;

  Sgl_linked_list_node() : Sgl_linked_list_node_base(), m_value(){};

  template <typename... Args>
  Sgl_linked_list_node(Args&&... t_args) : Sgl_linked_list_node_base(), m_value(std::forward<Args>(t_args)...){};
};

template <typename Tp> class Sgl_linked_list_iterator
{
  typedef Sgl_linked_list_iterator<Tp> self;

public:
  typedef Tp value_type;
  typedef Tp* pointer;
  typedef Tp& reference;
  typedef std::ptrdiff_t difference_type;
  typedef std::forward_iterator_tag iterator_category;
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
  operator==(const self& t_lhs, const self& t_rhs) noexcept
  {
    return t_lhs.m_ptr == t_rhs.m_ptr;
  };

  friend bool
  operator!=(const self& t_lhs, const self& t_rhs) noexcept
  {
    return t_lhs.m_ptr != t_rhs.m_ptr;
  };

  Sgl_linked_list_node_base* m_ptr;
};

template <typename Tp> class Sgl_linked_list_const_iterator
{
  typedef Sgl_linked_list_const_iterator<Tp> self;

public:
  typedef Tp value_type;
  typedef const Tp* pointer;
  typedef const Tp& reference;
  typedef std::ptrdiff_t difference_type;
  typedef std::forward_iterator_tag iterator_category;

  Sgl_linked_list_const_iterator() : m_ptr(nullptr){};

  explicit Sgl_linked_list_const_iterator(Sgl_linked_list_node_base* t_ptr) noexcept : m_ptr(t_ptr){};

  explicit Sgl_linked_list_const_iterator(const Sgl_linked_list_iterator<Tp>& t_itr) : m_ptr(t_itr.m_ptr){};

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

  friend bool
  operator==(const self& t_lhs, const self& t_rhs) noexcept
  {
    return t_lhs.m_ptr == t_rhs.m_ptr;
  };

  friend bool
  operator!=(const self& t_lhs, const self& t_rhs) noexcept
  {
    return t_lhs.m_ptr != t_rhs.m_ptr;
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

  template <typename Itr> using Iterator_category = typename std::iterator_traits<Itr>::iterator_category;

  template <typename Itr>
  using Requires_input_itr = std::enable_if<std::is_convertible_v<Iterator_category<Itr>, std::input_iterator_tag>>;

public:
  typedef Tp value_type;
  typedef Tp& reference;
  typedef const Tp& const_reference;
  typedef Sgl_linked_list_iterator<Tp> iterator;
  typedef Sgl_linked_list_const_iterator<Tp> const_iterator;
  typedef std::ptrdiff_t difference_type;
  typedef std::size_t size_type;

  Single_linked_list() noexcept : m_head(), m_alloc(node_alloc()){};

  explicit Single_linked_list(const Alloc& t_alloc) noexcept : m_head(), m_alloc(node_alloc(t_alloc)){};

  explicit Single_linked_list(size_type t_size, const Alloc& t_alloc = Alloc()) : m_head(), m_alloc(node_alloc(t_alloc))
  {
    m_default_init(t_size);
  };

  Single_linked_list(size_type t_size, const Tp& t_value, const Alloc& t_alloc = Alloc())
      : m_head(), m_alloc(node_alloc(t_alloc))
  {
    m_default_init(t_size, t_value);
  };

  template <typename InputIter, typename = Requires_input_itr<InputIter>>
  Single_linked_list(InputIter t_first, InputIter t_last, const Alloc& t_alloc = Alloc())
      : m_head(), m_alloc(node_alloc(t_alloc))
  {
    m_range_init(t_first, t_last);
  }

  Single_linked_list(std::initializer_list<Tp> t_list, const Alloc& t_alloc = Alloc())
      : m_head(), m_alloc(node_alloc(t_alloc))
  {
    m_range_init(t_list.begin(), t_list.end());
  }

  Single_linked_list(const Single_linked_list& t_list)
      : m_head(), m_alloc(alloc_traits::select_on_container_copy_construction(t_list.m_alloc))
  {
    m_range_init(t_list.cbegin(), t_list.cend());
  };

  Single_linked_list(Single_linked_list&& t_list) noexcept : m_head(), m_alloc(std::move(t_list.m_alloc))
  {
    m_move_assign(std::move(t_list));
  };

  ~Single_linked_list()
  {
    clear();
  }

  Single_linked_list&
  operator=(std::initializer_list<Tp> t_list)
  {
    m_copy_assign(t_list.begin(), t_list.end());
    return *this;
  }

  Single_linked_list&
  operator=(const Single_linked_list& t_list)
  {
    if(std::addressof(t_list) != this)
      {
        if(alloc_traits::propagate_on_container_copy_assignment::value)
          {
            if(alloc_traits::is_always_equal::value)
              {
                if(m_alloc != t_list.m_alloc)
                  clear();
              }

            m_alloc = alloc_traits::select_on_container_copy_construction(t_list.m_alloc);
          }

        m_copy_assign(t_list.cbegin(), t_list.cend());
      }

    return *this;
  }

  Single_linked_list&
  operator=(Single_linked_list&& t_list) noexcept(std::is_nothrow_move_constructible<node_alloc>::value)
  {
    if(alloc_traits::propagate_on_container_move_assignment::value || alloc_traits::is_always_equal::value)
      {
        m_move_assign(std::move(t_list));
        m_alloc = std::move(t_list.m_alloc);
      }
    else
      {
        if(m_alloc == t_list.m_alloc)
          m_move_assign(std::move(t_list));
        else
          m_copy_assign(std::move_iterator(t_list.begin()), std::move_iterator(t_list.end()));
      }

    return *this;
  }

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
    m_insert_after(const_cast<node_base*>(cbefore_begin().m_ptr), t_value);
  }

  void
  push_front(Tp&& t_value)
  {
    m_insert_after(const_cast<node_base*>(cbefore_begin().m_ptr), std::move(t_value));
  }

  template <typename... Args>
  void
  emplace_front(Args&&... t_args)
  {
    iterator(m_insert_after(const_cast<node_base*>(cbefore_begin().m_ptr), std::forward<Args>(t_args)...));
  }

  iterator
  insert_after(const_iterator t_pos, const Tp& t_value)
  {
    return iterator(m_insert_after(const_cast<node_base*>(t_pos.m_ptr), t_value));
  }

  iterator
  insert_after(const_iterator t_pos, Tp&& t_value)
  {
    return iterator(m_insert_after(const_cast<node_base*>(t_pos.m_ptr), std::move(t_value)));
  }

  iterator
  insert_after(const_iterator t_pos, size_type t_count, const Tp& t_value)
  {
    if(t_count)
      {
        Single_linked_list tmp__(t_count, t_value, m_alloc);
        return m_splice_after(t_pos, tmp__.before_begin(), tmp__.end());
      }

    return iterator(const_cast<node_base*>(t_pos.m_ptr));
  }

  template <typename InputItr, typename = Requires_input_itr<InputItr>>
  iterator
  insert_after(const_iterator t_pos, InputItr t_first, InputItr t_last) noexcept
  {
    Single_linked_list tmp__(t_first, t_last, m_alloc);

    if(!tmp__.empty())
      {
        return m_splice_after(t_pos, tmp__.cbefore_begin(), tmp__.cend());
      }

    return iterator(const_cast<node_base*>(t_pos.m_ptr));
  }

  iterator
  insert_after(const_iterator t_pos, std::initializer_list<Tp> t_list) noexcept
  {
    Single_linked_list tmp__(t_list);

    if(!tmp__.empty())
      {
        return m_splice_after(t_pos, tmp__.before_begin(), tmp__.end());
      }

    return iterator(t_pos.m_ptr);
  }

  template <typename... Args>
  iterator
  emplace_after(const_iterator t_pos, Args&&... t_args)
  {
    return iterator(m_insert_after(const_cast<node_base*>(t_pos.m_ptr), std::forward<Args>(t_args)...));
  }

  reference
  front() noexcept
  {
    return std::addressof(static_cast<node*>(&m_head.m_ptr_next)->m_value);
  }

  const_reference
  front() const noexcept
  {
    return std::addressof(static_cast<node*>(&m_head.m_ptr_next)->m_value);
  }

  iterator
  erase_after(const_iterator t_pos) noexcept
  {
    return m_erase_after(t_pos);
  }

  iterator
  erase_after(const_iterator t_first, const_iterator t_last) noexcept
  {
    node_base* to__ = const_cast<node_base*>(t_first.m_ptr);

    while(to__->m_ptr_next != t_last.m_ptr)
      to__ = m_erase_after(to__);

    return iterator(to__);
  }

  iterator
  splice_after(const_iterator t_pos, Single_linked_list&& t_list) noexcept
  {
    if(!t_list.empty())
      return m_splice_after(t_pos, t_list.cbefore_begin(), t_list.cend());

    return iterator(const_cast<node_base*>(t_pos.m_ptr));
  }

  iterator
  splice_after(const_iterator t_pos, const_iterator t_first, const_iterator t_last) noexcept
  {
    return m_splice_after(t_pos, t_first, t_last);
  }

  void
  remove(const Tp& t_value)
  {
    node_base* curr__ = &m_head;
    node_base* extra__ = nullptr;

    while(node* tmp__ = static_cast<node*>(curr__->m_ptr_next))
      {
        if(tmp__->m_value == t_value)
          {
            if(std::addressof(t_value) != std::addressof(tmp__->m_value))
              {
                m_erase_after(curr__);
                continue;
              }
            else
              extra__ = curr__;
          }

        curr__ = curr__->m_ptr_next;
      }

    if(extra__)
      m_erase_after(extra__);
  }

  template <typename... Args>
  void
  resize(size_type t_size, Args&&... t_args)
  {
    size_type size__ = size();

    if(size__ == t_size)
      return;

    iterator k__ = before_begin();

    for(size_type i = 0; i < t_size; ++i)
      ++k__;

    if(size__ > t_size)
      erase_after(k__, end());
    else
      insert_after(k__, t_size - size__, std::forward<Args>(t_args)...);
  };

  void
  reverse() const noexcept
  {
    node_base* tail__ = m_head.m_ptr_next;

    if(!tail__)
      return;

    while(node_base* tmp__ = tail__->m_ptr_next)
      {
        node_base* keep__ = m_head.m_ptr_next;
        m_head.m_ptr_next = tmp__;
        tail__->m_ptr_next = tmp__->m_ptr_next;
        m_head.m_ptr_next->m_ptr_next = keep__;
      }
  };

  void
  clear() noexcept
  {
    erase_after(cbefore_begin(), cend());
  };

  size_type
  size() const noexcept
  {
    size_type size__ = 0;

    for(auto itr__ = cbegin(), end__ = cend(); itr__ != end__; ++itr__)
      ++size__;

    return size__;
  };

  bool
  empty() const noexcept
  {
    return m_head.m_ptr_next == nullptr;
  };

protected:
  template <typename... Args>
  node*
  m_create_node(Args&&... t_args)
  {
    node* thing__ = alloc_traits::allocate(m_alloc, 1);

    try
      {
        alloc_traits::construct(m_alloc, thing__, std::forward<Args>(t_args)...);
      }
    catch(...)
      {
        alloc_traits::deallocate(m_alloc, thing__, 1);
        throw;
      }

    return thing__;
  }

  template <typename... Args>
  node_base*
  m_insert_after(node_base* t_pos, Args&&... t_args)
  {
    node* thing__ = m_create_node(std::forward<Args>(t_args)...);

    thing__->m_ptr_next = t_pos->m_ptr_next;
    t_pos->m_ptr_next = thing__;
    return t_pos->m_ptr_next;
  }

  node_base*
  m_erase_after(node_base* t_pos) noexcept
  {
    node* curr__ = static_cast<node*>(t_pos->m_ptr_next);

    t_pos->m_ptr_next = static_cast<node_base*>(curr__->m_ptr_next);

    alloc_traits::destroy(m_alloc, curr__);
    alloc_traits::deallocate(m_alloc, curr__, 1);

    return t_pos->m_ptr_next;
  }

  iterator
  m_splice_after(const_iterator t_pos, const_iterator t_first, const_iterator t_last) noexcept
  {
    node_base* tmp__ = const_cast<node_base*>(t_pos.m_ptr);
    node_base* begin__ = const_cast<node_base*>(t_first.m_ptr);
    node_base* end__ = begin__;

    while(end__ && end__->m_ptr_next != t_last.m_ptr)
      end__ = end__->m_ptr_next;

    if(begin__ != end__)
      return iterator(tmp__->m_transfer_after(begin__, end__));
    else
      return iterator(tmp__);
  }

  template <typename... Args>
  void
  m_default_init(size_type t_size, Args&&... t_args)
  {
    node_base* to__ = &m_head;

    for(; t_size; --t_size)
      {
        to__->m_ptr_next = m_create_node(std::forward<Args>(t_args)...);
        to__ = to__->m_ptr_next;
      }
  }

  template <typename InputIter>
  void
  m_range_init(InputIter t_first, InputIter t_last)
  {
    node_base* to__ = &m_head;

    for(; t_first != t_last; ++t_first)
      {
        to__->m_ptr_next = m_create_node(*t_first);
        to__ = to__->m_ptr_next;
      }
  }

  template <typename InputIter>
  void
  m_copy_assign(InputIter t_first, InputIter t_last)
  {
    auto prev__ = cbefore_begin();
    auto cur__ = begin();
    auto end__ = cend();

    while(cur__ != end__ && t_first != t_last)
      {
        *cur__ = *t_first;
        ++prev__;
        ++cur__;
        ++t_first;
      }

    if(t_first != t_last)
      insert_after(prev__, t_first, t_last);
    else if(cur__ != end__)
      erase_after(prev__, end__);
  }

  void
  m_move_assign(Single_linked_list&& t_list) noexcept
  {
    clear();

    m_head.m_ptr_next = t_list.m_head.m_ptr_next;
    t_list.m_head.m_ptr_next = nullptr;
  }

protected:
  node_base m_head;
  node_alloc m_alloc;
};

}

#endif