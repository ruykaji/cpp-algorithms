#include <string>

#include "../../include/simple_unit_test.hpp"

#include "./priority_queue.hpp"

TEST_CASE("Should insert value in the right place.")
{
    PriorityQueue<std::string> priorityQueue;

    priorityQueue.insert("a", 1);
    priorityQueue.insert("b", 2);
    priorityQueue.insert("c", 3);
    priorityQueue.insert("d", 4);
    priorityQueue.insert("e", 5);
    priorityQueue.insert("f", 6);

    ASSERT(priorityQueue.peek() == "a");
    ASSERT(priorityQueue == std::vector<std::string>({ "a", "b", "c", "d", "e", "f" }));
}

TEST_CASE("Should pop max element and restore priority queue main property.")
{
    PriorityQueue<std::string> priorityQueue;

    priorityQueue.insert("a", 1);
    priorityQueue.insert("b", 2);
    priorityQueue.insert("c", 3);
    priorityQueue.insert("d", 4);
    priorityQueue.insert("e", 5);
    priorityQueue.insert("f", 6);

    ASSERT(priorityQueue.pop() == "a");
    ASSERT(priorityQueue.peek() == "b");
    ASSERT(priorityQueue == std::vector<std::string>({ "b", "d", "c", "f", "e" }));
}