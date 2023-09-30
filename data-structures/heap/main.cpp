#include "../../include/simple_unit_test.hpp"

#include "./heap.hpp"

TEST_CASE("Should insert value in the right place.")
{
    MaxHeap<int> heap;

    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(1);
    heap.insert(3);
    heap.insert(35);

    ASSERT(heap.peek() == 35);

    std::vector<int> compareTo = { 35, 10, 20, 1, 3, 5 };

    ASSERT(heap == compareTo);
}

TEST_CASE("Should pop max element and restore heap main property.")
{
    MaxHeap<int> heap;

    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(1);
    heap.insert(3);
    heap.insert(35);

    ASSERT(heap.pop() == 35);
    ASSERT(heap.peek() == 20);

    std::vector<int> compareTo = { 20, 10, 5, 1, 3 };

    ASSERT(heap == compareTo);
}