#include <memory>

#ifndef DOUBLY_LINKED_LIST_NODE_H
#define DOUBLY_LINKED_LIST_NODE_H

template <class T> class DoublyLinkedListNode
{
    template <class U> friend class DoublyLinkedList;

    std::shared_ptr<DoublyLinkedListNode<T>> m_ptrPrev{};
    std::shared_ptr<DoublyLinkedListNode<T>> m_ptrNext{};
    T m_value{};

  public:
    DoublyLinkedListNode() = default;

    DoublyLinkedListNode(const std::shared_ptr<DoublyLinkedListNode<T>> &t_prev,
                         const std::shared_ptr<DoublyLinkedListNode<T>> &t_next, const T &t_value)
        : m_ptrPrev(t_prev), m_ptrNext(t_next), m_value(t_value){};

    void setValue(const T &t_value)
    {
        m_value = t_value;
    };

    std::shared_ptr<DoublyLinkedListNode<T>> getPrev()
    {
        return m_ptrPrev;
    };

    std::shared_ptr<DoublyLinkedListNode<T>> getNext()
    {
        return m_ptrNext;
    };

    T getValue()
    {
        return m_value;
    };
};

#endif