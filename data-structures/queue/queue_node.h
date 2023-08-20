#ifndef QUEUE_NODE_H
#define QUEUE_NODE_H

#include <memory>

#include "./queue.h"

template <class T> class QueueNode
{
    template <class U> friend class Queue;

    std::shared_ptr<QueueNode<T>> m_ptrPrev{};
    T m_value{};

  public:
    QueueNode() = default;
    QueueNode(const std::shared_ptr<QueueNode<T>> &t_prev, const T &t_value) : m_ptrPrev(t_prev), m_value(t_value){};

    T getValue()
    {
        return m_value;
    }
};

#endif