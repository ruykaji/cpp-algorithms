#ifndef __DOUBLY_LINKED_LIST_HPP__
#define __DOUBLY_LINKED_LIST_HPP__

#include <initializer_list>
#include <iterator>
#include <memory>
#include <utility>

namespace dsa
{
struct Dbl_linked_list_node_base
{
  Dbl_linked_list_node_base* m_next;
  Dbl_linked_list_node_base* m_prev;

  Dbl_linked_list_node_base() noexcept : m_prev(nullptr), m_next(nullptr){};
};

struct Dbl_linked_list_node_header : public Dbl_linked_list_node_base
{
  Dbl_linked_list_node_header() : Dbl_linked_list_node_base()
  {
    m_next = m_prev = this;
  };
};

template <typename Tp> struct Dbl_linked_list_node : public Dbl_linked_list_node_base
{
  Tp m_value;

  template <typename... Args>
  explicit Dbl_linked_list_node(Args&&... args) noexcept
      : Dbl_linked_list_node_base(), m_value(std::forward<Args>(args)...){};
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
  operator*() const noexcept
  {
    return static_cast<Dbl_linked_list_node<Tp>*>(m_node)->m_value;
  }

  pointer
  operator->() const noexcept
  {
    return std::addressof(static_cast<Dbl_linked_list_node<Tp>*>(m_node)->m_value);
  }

  Dbl_linked_list_iterator
  operator++() noexcept
  {
    Dbl_linked_list_iterator tmp__(*this);
    m_node = m_node->m_next;
    return tmp__;
  }

  Dbl_linked_list_iterator&
  operator++(int) noexcept
  {
    m_node = m_node->m_next;
    return *this;
  }

  Dbl_linked_list_iterator
  operator--() noexcept
  {
    Dbl_linked_list_iterator tmp__(*this);
    m_node = m_node->m_prev;
    return tmp__;
  }

  Dbl_linked_list_iterator&
  operator--(int) noexcept
  {
    m_node = m_node->m_prev;
    return *this;
  }

  friend bool
  operator==(const Dbl_linked_list_iterator& lhs, const Dbl_linked_list_iterator& rhs) noexcept
  {
    return lhs.m_node == rhs.m_node;
  }

  friend bool
  operator!=(const Dbl_linked_list_iterator& lhs, const Dbl_linked_list_iterator& rhs) noexcept
  {
    return lhs.m_node != rhs.m_node;
  }

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

  Dbl_linked_list_const_iterator(const Dbl_linked_list_node_base* node) noexcept : m_node(node){};

  Dbl_linked_list_const_iterator(const Dbl_linked_list_iterator<Tp>& itr) noexcept : m_node(itr.m_node){};

  reference
  operator*() const noexcept
  {
    return static_cast<const Dbl_linked_list_node<Tp>*>(m_node)->m_value;
  }

  pointer
  operator->() const noexcept
  {
    return std::addressof(static_cast<const Dbl_linked_list_node<Tp>*>(m_node)->m_value);
  }

  Dbl_linked_list_const_iterator
  operator++() noexcept
  {
    Dbl_linked_list_const_iterator tmp__(*this);
    m_node = m_node->m_next;
    return tmp__;
  }

  Dbl_linked_list_const_iterator&
  operator++(int) noexcept
  {
    m_node = m_node->m_next;
    return *this;
  }

  Dbl_linked_list_const_iterator
  operator--() noexcept
  {
    Dbl_linked_list_const_iterator tmp__(*this);
    m_node = m_node->m_prev;
    return tmp__;
  }

  Dbl_linked_list_const_iterator&
  operator--(int) noexcept
  {
    m_node = m_node->m_prev;
    return *this;
  }

  friend bool
  operator==(const Dbl_linked_list_const_iterator& lhs, const Dbl_linked_list_const_iterator& rhs) noexcept
  {
    return lhs.m_node == rhs.m_node;
  }

  friend bool
  operator!=(const Dbl_linked_list_const_iterator& lhs, const Dbl_linked_list_const_iterator& rhs) noexcept
  {
    return lhs.m_node != rhs.m_node;
  }

  const Dbl_linked_list_node_base* m_node;
};

template <typename Tp, typename Alloc = std::allocator<Tp>> class Doubly_linked_list
{
  static_assert(std::is_same<typename std::remove_cv<Tp>::type, Tp>::value,
                "sda::Doubly_linked_list must have a non-const, non-volatile value_type");

  static_assert(std::is_same<typename Alloc::value_type, Tp>::value,
                "sda::Doubly_linked_list must have the same value_type as its allocator");

private:
  typedef Dbl_linked_list_node_base node_base;
  typedef Dbl_linked_list_node_header node_header;
  typedef Dbl_linked_list_node<Tp> node;
  typedef typename std::allocator_traits<Alloc>::rebind_alloc<node> alloc_node;
  typedef std::allocator_traits<alloc_node> alloc_traits;

  using Self = Doubly_linked_list<Tp>;

  template <typename Itr>
  using Requires_input_itr = std::enable_if<
      std::is_convertible_v<typename std::iterator_traits<Itr>::iterator_category, std::input_iterator_tag>>;

public:
  typedef Tp value_type;
  typedef Alloc allocator_type;
  typedef Tp& reference;
  typedef const Tp& const_reference;
  typedef Dbl_linked_list_iterator<Tp> iterator;
  typedef Dbl_linked_list_const_iterator<Tp> const_iterator;
  typedef std::ptrdiff_t difference_type;
  typedef std::size_t size_type;

  Doubly_linked_list(const allocator_type& alloc = allocator_type()) noexcept : m_head(), m_alloc(alloc_node(alloc)){};

  Doubly_linked_list(size_type size, const allocator_type& alloc = allocator_type())
      : m_head(), m_alloc(alloc_node(alloc))
  {
    m_default_init(size);
  };

  explicit Doubly_linked_list(size_type size, const Tp& value, const allocator_type& alloc = allocator_type())
      : m_head(), m_alloc(alloc_node(alloc))
  {
    m_default_init(size, value);
  };

  Doubly_linked_list(std::initializer_list<Tp> list) : m_head(), m_alloc(alloc_node())
  {
    m_range_init(list.begin(), list.end());
  };

  template <typename Itr, typename = Requires_input_itr<Itr>>
  Doubly_linked_list(Itr first, Itr last, const allocator_type& alloc = allocator_type())
      : m_head(), m_alloc(alloc_node(alloc))
  {
    m_range_init(first, last);
  };

  Doubly_linked_list(const Self& list)
      : m_head(), m_alloc(alloc_traits::select_on_container_copy_construction(list.m_alloc))
  {
    m_range_init(list.cbegin(), list.cend());
  };

  Doubly_linked_list(Self&& list) noexcept : m_head(), m_alloc(std::move(list.m_alloc))
  {
    m_move_assignment(std::move(list));
  };

  ~Doubly_linked_list()
  {
    clear();
  }

  Self&
  operator=(std::initializer_list<Tp> list)
  {
    m_copy_assignment(list.begin(), list.end());
    return *this;
  }

  Self&
  operator=(const Self& list)
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

        m_copy_assignment(list.cbegin(), list.cend());
      }

    return *this;
  }

  Self&
  operator=(Self&& list) noexcept(std::is_nothrow_move_constructible<alloc_node>::value)
  {
    if(alloc_traits::propagate_on_container_move_assignment::value || alloc_traits::is_always_equal::value)
      {
        m_move_assignment(std::move(list));
        m_alloc = std::move(list.m_alloc);
      }
    else
      {
        if(m_alloc == list.m_alloc)
          m_move_assignment(std::move(list));
        else
          m_copy_assignment(std::make_move_iterator(list.begin()), std::make_move_iterator(list.end()));
      }

    return *this;
  }

  iterator
  begin() noexcept
  {
    return iterator(m_head.m_next);
  }

  const_iterator
  begin() const noexcept
  {
    return const_iterator(m_head.m_next);
  }

  const_iterator
  cbegin() const noexcept
  {
    return const_iterator(m_head.m_next);
  }

  iterator
  end() noexcept
  {
    return iterator(&m_head);
  }

  const_iterator
  end() const noexcept
  {
    return const_iterator(&m_head);
  }

  const_iterator
  cend() const noexcept
  {
    return const_iterator(&m_head);
  }

  reference
  front() noexcept
  {
    return static_cast<node*>(m_head.m_next)->m_value;
  }

  const_reference
  front() const noexcept
  {
    return static_cast<node*>(m_head.m_next)->m_value;
  }

  reference
  back() noexcept
  {
    return static_cast<node*>(m_head.m_prev)->m_value;
  }

  const_reference
  back() const noexcept
  {
    return static_cast<node*>(m_head.m_prev)->m_value;
  }

  void
  push_front(const Tp& value)
  {
    m_insert(m_head.m_next, value);
  }

  void
  push_front(Tp&& value)
  {
    m_insert(m_head.m_next, std::move(value));
  }

  void
  push_back(const Tp& value)
  {
    m_insert(&m_head, value);
  }

  void
  push_back(Tp&& value)
  {
    m_insert(&m_head, std::move(value));
  }

  template <typename... Args>
  void
  emplace(const_iterator pos, Args&&... args)
  {
    m_insert(const_cast<node_base*>(pos.m_node), std::forward<Args>(args)...);
  }

  template <typename... Args>
  void
  emplace_front(Args&&... args)
  {
    m_insert(m_head.m_next, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void
  emplace_back(Args&&... args)
  {
    m_insert(&m_head, std::forward<Args>(args)...);
  }

  iterator
  insert(const_iterator pos, const Tp& value)
  {
    return iterator(m_insert(const_cast<node_base*>(pos.m_node), value));
  }

  iterator
  insert(const_iterator pos, Tp&& value)
  {
    return iterator(m_insert(const_cast<node_base*>(pos.m_node), std::move(value)));
  }

  iterator
  insert(const_iterator pos, size_type count, const Tp& value)
  {
    if(count)
      {
        Self tmp(count, value);
        m_splice(pos, tmp.begin(), tmp.end());
        return iterator(const_cast<node_base*>(pos.m_node)->m_prev);
      }

    return iterator(const_cast<node_base*>(pos.m_node));
  }

  template <typename Itr, typename = Requires_input_itr<Itr>>
  iterator
  insert(const_iterator pos, Itr first, Itr last)
  {
    Self tmp(first, last);

    if(!tmp.empty())
      {
        m_splice(pos, tmp.begin(), tmp.end());
        return iterator(const_cast<node_base*>(pos.m_node)->m_prev);
      }

    return iterator(const_cast<node_base*>(pos.m_node));
  }

  iterator
  erase(const_iterator pos) noexcept
  {
    return iterator(m_erase(const_cast<node_base*>(pos.m_node)));
  }

  iterator
  erase(const_iterator first, const_iterator last) noexcept
  {
    node_base* curr__ = const_cast<node_base*>(first.m_node);
    const node_base* end__ = static_cast<const node_base*>(last.m_node);

    while(curr__ != end__)
      curr__ = m_erase(curr__);

    return iterator(curr__);
  }

  void
  splice(const_iterator pos, Self&& list) noexcept
  {
    if(!list.empty())
      m_splice(pos, list.begin(), list.end());
  }

  void
  splice(const_iterator pos, Self& list) noexcept
  {
    if(!list.empty())
      m_splice(pos, list.begin(), list.end());
  }

  void
  splice(const_iterator pos, const_iterator first, const_iterator last) noexcept
  {
    if(first != last)
      m_splice(pos, first, last);
  }

  void
  clear() noexcept
  {
    node_base* thing__ = m_head.m_next;

    while(thing__->m_next != thing__)
      thing__ = m_erase(thing__);
  }

  size_type
  size() const noexcept
  {
    size_type size__ = 0;
    const node_base* end__ = &m_head;
    node_base* curr__ = m_head.m_next;

    while(curr__ != end__)
      {
        curr__ = curr__->m_next;
        ++size__;
      }

    return size__;
  }

  bool
  empty()
  {
    return m_head.m_next == &m_head;
  }

private:
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
  void
  m_default_init(size_type size, Args&&... args)
  {
    node_base* to__ = &m_head;

    for(; size; --size)
      {
        node_base* tmp__ = to__;

        to__->m_next = static_cast<node_base*>(m_create_node(std::forward<Args>(args)...));
        to__ = to__->m_next;
        to__->m_prev = tmp__;
      }

    node_base* head__ = &m_head;

    head__->m_prev = to__;
    to__->m_next = head__;
  }

  template <typename Itr>
  void
  m_range_init(Itr first, Itr last)
  {
    node_base* to__ = &m_head;

    for(; first != last; ++first)
      {
        node_base* tmp__ = to__;

        to__->m_next = static_cast<node_base*>(m_create_node(*first));
        to__ = to__->m_next;
        to__->m_prev = tmp__;
      }

    node_base* head__ = &m_head;

    head__->m_prev = to__;
    to__->m_next = head__;
  }

  template <typename Itr>
  void
  m_copy_assignment(Itr first, Itr last)
  {
    iterator cur__ = begin();
    iterator end__ = end();

    while(first != last && cur__ != end__)
      {
        *cur__ = *first;
        ++cur__;
        ++first;
      }

    if(cur__ == end__)
      insert(end__, first, last);
    else if(first == last)
      erase(++cur__, end__);
  }

  void
  m_move_assignment(Self&& list) noexcept
  {
    clear();

    if(&list.m_head != list.m_head.m_next)
      {
        m_head.m_next = list.m_head.m_next;
        m_head.m_prev = list.m_head.m_prev;

        m_head.m_next->m_prev = &m_head;
        m_head.m_prev->m_next = &m_head;

        list.m_head.m_next = list.m_head.m_prev = &list.m_head;
      }
  }

  template <typename... Args>
  node_base*
  m_insert(node_base* pos, Args&&... args)
  {
    node_base* thing__ = static_cast<node_base*>(m_create_node(std::forward<Args>(args)...));
    node_base* prev__ = pos->m_prev;

    pos->m_prev = thing__;
    prev__->m_next = thing__;
    thing__->m_prev = prev__;
    thing__->m_next = pos;

    return thing__;
  }

  node_base*
  m_erase(node_base* pos) noexcept
  {
    node_base* next__ = pos->m_next;
    node_base* prev__ = pos->m_prev;

    alloc_traits::destroy(m_alloc, static_cast<node*>(pos));
    alloc_traits::deallocate(m_alloc, static_cast<node*>(pos), 1);

    next__->m_prev = prev__;
    prev__->m_next = next__;

    return next__;
  }

  void
  m_splice(const_iterator pos, const_iterator first, const_iterator last)
  {
    node_base* curr__ = const_cast<node_base*>(pos.m_node);
    node_base* first__ = const_cast<node_base*>(first.m_node);
    node_base* last__ = const_cast<node_base*>(last.m_node);

    node_base* last_prev__ = last__->m_prev;

    last__->m_prev = first__->m_prev;
    last__->m_prev->m_next = last__;

    first__->m_prev = curr__->m_prev;
    first__->m_prev->m_next = first__;

    curr__->m_prev = last_prev__;
    last_prev__->m_next = curr__;
  }

private:
  node_header m_head;
  alloc_node m_alloc;
};

}

#endif