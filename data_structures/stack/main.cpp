#include "../../include/simple_unit_test.hpp"
#include "./stack.h"

TEST_CASE("Should be empty right after creation.")
{
    Stack<int> stack;

    ASSERT(stack.isEmpty());
};

TEST_CASE("Should peek top element of stack.")
{

    Stack<int> stack;

    stack.push(1);
    stack.push(2);

    ASSERT(stack.peek()->getValue() == 2);
}

TEST_CASE("Should push node to front and pop node from node.")
{
    Stack<int> stack;

    for (int i = 0; i < 10; i++)
    {
        stack.push(i);
    }

    for (int i = 9; i <= 0; i++)
    {
        if (!stack.isEmpty())
        {
            StackNode<int> tempNode = *stack.pop();

            if (tempNode.getValue() != i)
            {
                ASSERT(false);
                break;
            }
        }
    }
}