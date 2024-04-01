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
  m_transfer_after(Sgl_linked_list_node_base* begin, Sgl_linked_list_node_base* end) noexcept
  {
    Sgl_linked_list_node_base* keep__ = begin->m_ptr_next;

    if(end)
      {
        begin->m_ptr_next = end->m_ptr_next;
        end->m_ptr_next = m_ptr_next;
      }
    else
      begin->m_ptr_next = nullptr;

    m_ptr_next = keep__;
    return end;
  }
};

template <typename Tp> struct Sgl_linked_list_node : public Sgl_linked_list_node_base
{
  Tp m_value;

  Sgl_linked_list_node() : Sgl_linked_list_node_base(), m_value(){};

  template <typename... Args>
  Sgl_linked_list_node(Args&&... args) : Sgl_linked_list_node_base(), m_value(std::forward<Args>(args)...){};
};

template <typename Tp> class Sgl_linked_list_iterator
{
  using Self = Sgl_linked_list_iterator<Tp>;

public:
  typedef Tp value_type;
  typedef Tp* pointer;
  typedef Tp& reference;
  typedef std::ptrdiff_t difference_type;
  typedef std::forward_iterator_tag iterator_category;
  Sgl_linked_list_iterator() : m_ptr(nullptr){};

  Sgl_linked_list_iterator(Sgl_linked_list_node_base* ptr) noexcept : m_ptr(ptr){};

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
  operator==(const Self& lhs, const Self& rhs) noexcept
  {
    return lhs.m_ptr == rhs.m_ptr;
  };

  friend bool
  operator!=(const Self& lhs, const Self& rhs) noexcept
  {
    return lhs.m_ptr != rhs.m_ptr;
  };

  Sgl_linked_list_node_base* m_ptr;
};

template <typename Tp> class Sgl_linked_list_const_iterator
{
  using Self = Sgl_linked_list_const_iterator<Tp>;

public:
  typedef Tp value_type;
  typedef const Tp* pointer;
  typedef const Tp& reference;
  typedef std::ptrdiff_t difference_type;
  typedef std::forward_iterator_tag iterator_category;

  Sgl_linked_list_const_iterator() : m_ptr(nullptr){};

  Sgl_linked_list_const_iterator(Sgl_linked_list_node_base* ptr) noexcept : m_ptr(ptr){};

  Sgl_linked_list_const_iterator(const Sgl_linked_list_iterator<Tp>& itr) : m_ptr(itr.m_ptr){};

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
  operator==(const Self& lhs, const Self& rhs) noexcept
  {
    return lhs.m_ptr == rhs.m_ptr;
  };

  friend bool
  operator!=(const Self& lhs, const Self& rhs) noexcept
  {
    return lhs.m_ptr != rhs.m_ptr;
  };

  const Sgl_linked_list_node_base* m_ptr;
};

template <typename Tp>
bool
operator==(const Sgl_linked_list_iterator<Tp>& lhs, const Sgl_linked_list_const_iterator<Tp>& rhs) noexcept
{
  return lhs.m_ptr == rhs.m_ptr;
};

template <typename Tp>
bool
operator!=(const Sgl_linked_list_iterator<Tp>& lhs, const Sgl_linked_list_const_iterator<Tp>& rhs) noexcept
{
  return lhs.m_ptr != rhs.m_ptr;
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
  typedef typename std::allocator_traits<Alloc>::rebind_alloc<node> alloc_node;
  typedef std::allocator_traits<alloc_node> alloc_traits;

  template <typename Itr>
  using Requires_input_itr = std::enable_if<
      std::is_convertible_v<typename std::iterator_traits<Itr>::iterator_category, std::input_iterator_tag>>;

public:
  typedef Tp value_type;
  typedef Alloc allocator_type;
  typedef Tp& reference;
  typedef const Tp& const_reference;
  typedef Sgl_linked_list_iterator<Tp> iterator;
  typedef Sgl_linked_list_const_iterator<Tp> const_iterator;
  typedef std::ptrdiff_t difference_type;
  typedef std::size_t size_type;

  Single_linked_list(const allocator_type& alloc = allocator_type()) noexcept : m_head(), m_alloc(alloc_node(alloc)){};

  explicit Single_linked_list(size_type size, const allocator_type& alloc = allocator_type())
      : m_head(), m_alloc(alloc_node(alloc))
  {
    m_default_init(size);
  };

  Single_linked_list(size_type size, const Tp& value, const allocator_type& alloc = allocator_type())
      : m_head(), m_alloc(alloc_node(alloc))
  {
    m_default_init(size, value);
  };

  template <typename InputIter, typename = Requires_input_itr<InputIter>>
  Single_linked_list(InputIter first, InputIter last, const allocator_type& alloc = allocator_type())
      : m_head(), m_alloc(alloc_node(alloc))
  {
    m_range_init(first, last);
  }

  Single_linked_list(std::initializer_list<Tp> list) : m_head(), m_alloc(alloc_node())
  {
    m_range_init(list.begin(), list.end());
  }

  Single_linked_list(const Single_linked_list& list)
      : m_head(), m_alloc(alloc_traits::select_on_container_copy_construction(list.m_alloc))
  {
    m_range_init(list.cbegin(), list.cend());
  };

  Single_linked_list(Single_linked_list&& list) noexcept : m_head(), m_alloc(std::move(list.m_alloc))
  {
    m_move_assign(std::move(list));
  };

  ~Single_linked_list()
  {
    clear();
  }

  Single_linked_list&
  operator=(std::initializer_list<Tp> list)
  {
    m_copy_assign(list.begin(), list.end());
    return *this;
  }

  Single_linked_list&
  operator=(const Single_linked_list& list)
  {
    if(std::addressof(list) != this)
      {
        if(alloc_traits::propagate_on_container_copy_assignment::value)
          {
            if(alloc_traits::is_always_equal::value)
              {
                if(m_alloc != list.m_alloc)
                  clear();
              }

            m_alloc = alloc_traits::select_on_container_copy_construction(list.m_alloc);
          }

        m_copy_assign(list.cbegin(), list.cend());
      }

    return *this;
  }

  Single_linked_list&
  operator=(Single_linked_list&& list) noexcept(std::is_nothrow_move_constructible<alloc_node>::value)
  {
    if(alloc_traits::propagate_on_container_move_assignment::value || alloc_traits::is_always_equal::value)
      {
        m_move_assign(std::move(list));
        m_alloc = std::move(list.m_alloc);
      }
    else
      {
        if(m_alloc == list.m_alloc)
          m_move_assign(std::move(list));
        else
          m_copy_assign(std::move_iterator(list.begin()), std::move_iterator(list.end()));
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
  push_front(const Tp& value) noexcept
  {
    m_insert_after(const_cast<node_base*>(cbefore_begin().m_ptr), value);
  }

  void
  push_front(Tp&& value)
  {
    m_insert_after(const_cast<node_base*>(cbefore_begin().m_ptr), std::move(value));
  }

  template <typename... Args>
  void
  emplace_front(Args&&... args)
  {
    m_insert_after(const_cast<node_base*>(cbefore_begin().m_ptr), std::forward<Args>(args)...);
  }

  iterator
  insert_after(const_iterator pos, const Tp& value)
  {
    return iterator(m_insert_after(const_cast<node_base*>(pos.m_ptr), value));
  }

  iterator
  insert_after(const_iterator pos, Tp&& value)
  {
    return iterator(m_insert_after(const_cast<node_base*>(pos.m_ptr), std::move(value)));
  }

  iterator
  insert_after(const_iterator pos, size_type t_count, const Tp& value)
  {
    if(t_count)
      {
        Single_linked_list tmp__(t_count, value, m_alloc);
        return m_splice_after(pos, tmp__.before_begin(), tmp__.end());
      }

    return iterator(const_cast<node_base*>(pos.m_ptr));
  }

  template <typename InputItr, typename = Requires_input_itr<InputItr>>
  iterator
  insert_after(const_iterator pos, InputItr first, InputItr last) noexcept
  {
    Single_linked_list tmp__(first, last, m_alloc);

    if(!tmp__.empty())
      {
        return m_splice_after(pos, tmp__.cbefore_begin(), tmp__.cend());
      }

    return iterator(const_cast<node_base*>(pos.m_ptr));
  }

  iterator
  insert_after(const_iterator pos, std::initializer_list<Tp> list) noexcept
  {
    Single_linked_list tmp__(list);

    if(!tmp__.empty())
      {
        return m_splice_after(pos, tmp__.before_begin(), tmp__.end());
      }

    return iterator(const_cast<node_base*>(pos.m_ptr));
  }

  template <typename... Args>
  iterator
  emplace_after(const_iterator pos, Args&&... t_args)
  {
    return iterator(m_insert_after(const_cast<node_base*>(pos.m_ptr), std::forward<Args>(t_args)...));
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
  erase_after(const_iterator pos) noexcept
  {
    return m_erase_after(const_cast<node_base*>(pos.m_ptr));
  }

  iterator
  erase_after(const_iterator first, const_iterator last) noexcept
  {
    node_base* to__ = const_cast<node_base*>(first.m_ptr);

    while(to__->m_ptr_next != last.m_ptr)
      m_erase_after(to__);

    return iterator(to__);
  }

  iterator
  splice_after(const_iterator pos, Single_linked_list& list) noexcept
  {
    if(!list.empty())
      return m_splice_after(pos, list.cbefore_begin(), list.cend());

    return iterator(const_cast<node_base*>(pos.m_ptr));
  }

  iterator
  splice_after(const_iterator pos, Single_linked_list&& list) noexcept
  {
    if(!list.empty())
      return m_splice_after(pos, list.cbefore_begin(), list.cend());

    return iterator(const_cast<node_base*>(pos.m_ptr));
  }

  iterator
  splice_after(const_iterator pos, const_iterator first, const_iterator last) noexcept
  {
    return m_splice_after(pos, first, last);
  }

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
  m_create_node(Args&&... args)
  {
    node* thing__ = alloc_traits::allocate(m_alloc, 1);

    try
      {
        alloc_traits::construct(m_alloc, thing__, std::forward<Args>(args)...);
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
  m_insert_after(node_base* pos, Args&&... args)
  {
    node* thing__ = m_create_node(std::forward<Args>(args)...);

    thing__->m_ptr_next = pos->m_ptr_next;
    pos->m_ptr_next = thing__;
    return pos->m_ptr_next;
  }

  node_base*
  m_erase_after(node_base* pos) noexcept
  {
    node* curr__ = static_cast<node*>(pos->m_ptr_next);

    pos->m_ptr_next = static_cast<node_base*>(curr__->m_ptr_next);

    alloc_traits::destroy(m_alloc, curr__);
    alloc_traits::deallocate(m_alloc, curr__, 1);

    return pos->m_ptr_next;
  }

  iterator
  m_splice_after(const_iterator pos, const_iterator first, const_iterator last) noexcept
  {
    node_base* tmp__ = const_cast<node_base*>(pos.m_ptr);
    node_base* begin__ = const_cast<node_base*>(first.m_ptr);
    node_base* end__ = begin__;

    while(end__ && end__->m_ptr_next != last.m_ptr)
      end__ = end__->m_ptr_next;

    if(begin__ != end__)
      return iterator(tmp__->m_transfer_after(begin__, end__));
    else
      return iterator(tmp__);
  }

  template <typename... Args>
  void
  m_default_init(size_type size, Args&&... args)
  {
    node_base* to__ = &m_head;

    for(; size; --size)
      {
        to__->m_ptr_next = m_create_node(std::forward<Args>(args)...);
        to__ = to__->m_ptr_next;
      }
  }

  template <typename InputIter>
  void
  m_range_init(InputIter first, InputIter last)
  {
    node_base* to__ = &m_head;

    for(; first != last; ++first)
      {
        to__->m_ptr_next = m_create_node(*first);
        to__ = to__->m_ptr_next;
      }
  }

  template <typename InputIter>
  void
  m_copy_assign(InputIter first, InputIter last)
  {
    auto prev__ = cbefore_begin();
    auto cur__ = begin();
    auto end__ = cend();

    while(cur__ != end__ && first != last)
      {
        *cur__ = *first;
        ++prev__;
        ++cur__;
        ++first;
      }

    if(first != last)
      insert_after(prev__, first, last);
    else if(cur__ != end__)
      erase_after(prev__, end__);
  }

  void
  m_move_assign(Single_linked_list&& list) noexcept
  {
    clear();

    m_head.m_ptr_next = list.m_head.m_ptr_next;
    list.m_head.m_ptr_next = nullptr;
  }

protected:
  node_base m_head;
  alloc_node m_alloc;
};

}

#endif