#include <cstdint>

#include "doubly_linked_list_node.h"

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

template <class T> class DoublyLinkedList
{
    std::shared_ptr<DoublyLinkedListNode<T>> m_ptrHead{};
    std::shared_ptr<DoublyLinkedListNode<T>> m_ptrTail{};

  public:
    ~DoublyLinkedList()
    {
        clear();
    }

    void prepend(const T &t_value)
    {
        if (!m_ptrHead)
        {
            auto newHead = std::make_shared<DoublyLinkedListNode<T>>(DoublyLinkedListNode<T>({}, {}, t_value));
            m_ptrHead = newHead;
            m_ptrTail = newHead;
        }
        else
        {
            auto newHead = std::make_shared<DoublyLinkedListNode<T>>(DoublyLinkedListNode<T>({}, m_ptrHead, t_value));
            m_ptrHead->m_ptrPrev = newHead;
            m_ptrHead = newHead;
        }
    }

    void append(const T &t_value)
    {
        if (!m_ptrTail)
        {
            auto newTail = std::make_shared<DoublyLinkedListNode<T>>(DoublyLinkedListNode<T>({}, {}, t_value));
            m_ptrHead = newTail;
            m_ptrTail = newTail;
        }
        else
        {
            auto newTail = std::make_shared<DoublyLinkedListNode<T>>(DoublyLinkedListNode<T>(m_ptrTail, {}, t_value));
            m_ptrTail->m_ptrNext = newTail;
            m_ptrTail = newTail;
        }
    }

    void pop_front()
    {
        if (m_ptrHead)
        {
            auto newHead = m_ptrHead->m_ptrNext;

            if (newHead)
            {
                newHead->m_ptrPrev = {};
                m_ptrHead = newHead;
            }
            else
            {
                m_ptrHead = {};
                m_ptrTail = {};
            }
        }
    }

    void pop_back()
    {
        if (m_ptrHead)
        {
            auto newTail = m_ptrTail->m_ptrPrev;

            if (newTail)
            {
                newTail->m_ptrNext = {};
                m_ptrTail = newTail;
            }
            else
            {
                m_ptrHead = {};
                m_ptrTail = {};
            }
        }
    }

    void erase(const uint64_t &t_rawIndex)
    {
        if (m_ptrHead)
        {
            uint64_t itr{};

            for (auto i = m_ptrHead; i != nullptr; i = i->m_ptrNext, ++itr)
            {
                if (itr == t_rawIndex)
                {
                    if (i->m_ptrPrev)
                    {
                        if (i->m_ptrNext)
                        {
                            auto tempPrevNode = i->m_ptrPrev;
                            auto tempNextNode = i->m_ptrNext;

                            tempPrevNode->m_ptrNext = tempNextNode;
                            tempNextNode->m_ptrPrev = tempPrevNode;
                        }
                        else
                            pop_back();
                    }
                    else
                        pop_front();

                    break;
                }
            }
        }
    }

    std::shared_ptr<DoublyLinkedListNode<T>> findByValue(const T &t_value)
    {
        for (auto i = m_ptrHead; i != nullptr; i = i->m_ptrNext)
        {
            if (i->m_value == t_value)
                return i;
        }

        return nullptr;
    }

    std::shared_ptr<DoublyLinkedListNode<T>> findByRawIndex(const uint64_t &t_rawIndex)
    {
        uint64_t itr = 0;

        for (auto i = m_ptrHead; i != nullptr; i = i->m_ptrNext, ++itr)
        {
            if (itr == t_rawIndex)
                return i;
        }

        return nullptr;
    }

    void clear()
    {
        while (m_ptrHead)
        {
            pop_front();
        }
    }

    uint64_t size()
    {
        if (m_ptrHead)
        {
            uint64_t count{};

            for (auto i = m_ptrHead; i != nullptr; i = i->m_ptrNext)
                ++count;

            return count;
        }

        return 0;
    }

    std::shared_ptr<DoublyLinkedListNode<T>> insert(const T &t_value,const uint64_t &t_rawIndex)
    {
        if (m_ptrHead)
        {
            uint64_t itr{};

            for (auto i = m_ptrHead; i != nullptr; i = i->m_ptrNext, ++itr)
            {
                if (itr == t_rawIndex)
                {
                    if (i->m_ptrPrev)
                    {
                        auto newNode = std::make_shared<DoublyLinkedListNode<T>>(
                            DoublyLinkedListNode<T>(i->m_ptrPrev, i, t_value));

                        i->m_ptrPrev->m_ptrNext = newNode;
                        i->m_ptrPrev = newNode;

                        return i->m_ptrPrev;
                    }
                    else
                    {
                        prepend(t_value);

                        return m_ptrHead;
                    }
                };
            };
        }
        else
        {
            prepend(t_value);

            return m_ptrHead;
        }

        return nullptr;
    };

    std::shared_ptr<DoublyLinkedListNode<T>> begin()
    {
        return m_ptrHead;
    }

    std::shared_ptr<DoublyLinkedListNode<T>> end()
    {
        return m_ptrTail;
    }
};

#endif