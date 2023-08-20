#ifndef STACK_NODE_H
#define STACK_NODE_H

#include <memory>

#include "./stack.h"

template <class T> class StackNode
{
    template <class U> friend class Stack;

    std::shared_ptr<StackNode<T>> m_ptrPrev{};
    T m_value{};

  public:
    StackNode() = default;
    StackNode(const std::shared_ptr<StackNode<T>> t_prev, const T &t_value) : m_ptrPrev(t_prev), m_value(t_value){};

    T getValue()
    {
        return m_value;
    }
};

#endif