#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "./linked_list_node.h"

template <class T> class LinkedList
{
    std::shared_ptr<LinkedListNode<T>> m_ptrHead{};
    std::shared_ptr<LinkedListNode<T>> m_ptrTail{};

  public:
    LinkedList(){};

    void prepend(const T &t_value)
    {
        if (!m_ptrHead)
        {
            auto newHead = std::make_shared<LinkedListNode<T>>(LinkedListNode<T>({}, t_value));
            m_ptrHead = newHead;
            m_ptrTail = newHead;
        }
        else
        {
            auto newHead = std::make_shared<LinkedListNode<T>>(LinkedListNode<T>(m_ptrHead, t_value));
            m_ptrHead = newHead;
        }
    }

    void append(T t_value)
    {
        auto newTail = std::make_shared<LinkedListNode<T>>(LinkedListNode<T>({}, t_value));

        if (!m_ptrTail)
        {
            m_ptrHead = newTail;
            m_ptrTail = newTail;
        }
        else
        {
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
            std::shared_ptr<LinkedListNode<T>> newTail = {};

            for (auto i = m_ptrHead; i != nullptr; i = i->m_ptrNext)
            {
                if (i->m_ptrNext == m_ptrTail)
                {
                    newTail = i;
                    break;
                }
            }

            if (newTail)
            {
                m_ptrTail = newTail;
                m_ptrTail->m_ptrNext = {};
            }
            else
            {
                m_ptrHead = {};
                m_ptrTail = {};
            }
        }
    }

    std::shared_ptr<LinkedListNode<T>> findByValue(const T &t_value)
    {
        for (auto i = m_ptrHead; i != nullptr; i = i->m_ptrNext)
        {
            if (i->m_value == t_value)
            {
                return i;
            }
        }

        return nullptr;
    }

    std::shared_ptr<LinkedListNode<T>> findByRawIndex(const uint64_t &t_rawIndex)
    {
        uint64_t itr{};

        for (auto i = m_ptrHead; i != nullptr; i = i->m_ptrNext, ++itr)
        {
            if (itr == t_rawIndex)
            {
                return i;
            }
        }

        return nullptr;
    }

    void erase(const uint64_t &t_rawIndex)
    {
        if (m_ptrHead)
        {
            uint64_t itr{};
            std::shared_ptr<LinkedListNode<T>> tempPrevNode{};

            for (auto i = m_ptrHead; i != nullptr; tempPrevNode = i, i = i->m_ptrNext, ++itr)
            {
                if (itr == t_rawIndex)
                {
                    if (i != m_ptrHead)
                    {
                        if (i->m_ptrNext)
                        {
                            tempPrevNode->m_ptrNext = i->m_ptrNext;
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

    void clear()
    {
        while (m_ptrHead)
        {
            pop_front();
        }
    }

    int size()
    {
        if (m_ptrHead)
        {
            int count = 0;

            for (auto i = m_ptrHead; i != nullptr; i = i->m_ptrNext)
            {
                count++;
            }

            return count;
        }

        return 0;
    }

    std::shared_ptr<LinkedListNode<T>> insert(const T &t_value,const uint64_t &t_rawIndex)
    {
        if (m_ptrHead)
        {
            uint64_t itr{};
            std::shared_ptr<LinkedListNode<T>> tempPrevNode{};

            for (auto i = m_ptrHead; i != nullptr; tempPrevNode = i, i = i->m_ptrNext, itr++)
            {
                if (itr == t_rawIndex)
                {
                    if (i != m_ptrHead)
                    {
                        auto newNode = std::make_shared<LinkedListNode<T>>(LinkedListNode<T>(i, t_value));
                        tempPrevNode->m_ptrNext = newNode;

                        return newNode;
                    }
                    else
                    {
                        prepend(t_value);
                        break;
                    };
                };
            };
        }
        else
            prepend(t_value);

        return m_ptrHead;
    };

    std::shared_ptr<LinkedListNode<T>> begin()
    {
        return m_ptrHead;
    }

    std::shared_ptr<LinkedListNode<T>> end()
    {
        return m_ptrTail;
    }
};

#endif