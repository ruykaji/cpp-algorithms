#include "../../include/simple_unit_test.hpp"
#include "./queue.h"

TEST_CASE("Should be empty right after creation.")
{

    Queue<int> queue;

    ASSERT(queue.isEmpty());
};

TEST_CASE("Should add node to back of queue and return front node.")
{

    Queue<int> queue;

    for (int i = 0; i < 10; i++)
    {
        queue.enqueue(i);
    }

    for (int i = 0; i < 10; i++)
    {
        if (!queue.isEmpty())
        {
            QueueNode<int> tempNode = *queue.dequeue();

            if (tempNode.getValue() != i)
            {
                ASSERT(false);
                break;
            }
        }
    }
}