#ifndef LINKED_LIST_NODE_H
#define LINKED_LIST_NODE_H

#include <memory>

#include "./linked_list.h"

template <class T> class LinkedListNode
{
    template <class U> friend class LinkedList;

    std::shared_ptr<LinkedListNode<T>> m_ptrNext{};
    T m_value{};

  public:
    LinkedListNode() = default;
    LinkedListNode(const std::shared_ptr<LinkedListNode<T>> t_next, const T &t_value) : m_ptrNext(t_next), m_value(t_value){};

    void setValue(const T &t_value)
    {
        m_value = t_value;
    };

    std::shared_ptr<LinkedListNode<T>> getNext()
    {
        return m_ptrNext;
    };

    T getValue()
    {
        return m_value;
    };
};

#endif