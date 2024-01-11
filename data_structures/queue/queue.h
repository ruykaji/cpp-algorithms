#ifndef QUEUE_H
#define QUEUE_H

#include "./queue_node.h"

template <class T> class Queue
{
    std::shared_ptr<QueueNode<T>> m_ptrFront{};
    std::shared_ptr<QueueNode<T>> m_ptrBack{};

  public:
    Queue() = default;

    bool isEmpty()
    {
        return m_ptrBack == nullptr;
    }

    void enqueue(const T &t_value)
    {
        auto newBack = std::make_shared<QueueNode<T>>(QueueNode<T>({}, t_value));

        if (!isEmpty())
        {
            m_ptrBack->m_ptrPrev = newBack;
            m_ptrBack = newBack;
        }
        else
        {
            m_ptrBack = newBack;
            m_ptrFront = newBack;
        }
    }

    std::shared_ptr<QueueNode<T>> dequeue()
    {
        if (!isEmpty())
        {
            auto oldFront = m_ptrFront;
            auto newFront = m_ptrFront->m_ptrPrev;

            m_ptrFront = newFront;
            oldFront->m_ptrPrev = {};

            return oldFront;
        }

        return nullptr;
    }
};

#endif