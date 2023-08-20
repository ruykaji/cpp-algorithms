#ifndef STACK_H
#define STACK_H

#include "./stack_node.h"

template <class T> class Stack
{
    std::shared_ptr<StackNode<T>> m_ptrTop{};

  public:
    Stack() = default;

    bool isEmpty()
    {
        return m_ptrTop == nullptr;
    }

    void push(const T &t_value)
    {
        std::shared_ptr<StackNode<T>> newTop = std::make_shared<StackNode<T>>(StackNode<T>({}, (t_value)));
        m_ptrTop = newTop;
    }

    std::shared_ptr<StackNode<T>> pop()
    {
        if (!isEmpty())
        {
            auto oldTop = m_ptrTop;
            auto newTop = m_ptrTop->m_ptrPrev;

            m_ptrTop = newTop;
            oldTop->m_ptrPrev = nullptr;

            return oldTop;
        }

        return nullptr;
    }

    std::shared_ptr<StackNode<T>> peek()
    {
        return m_ptrTop;
    }
};

#endif