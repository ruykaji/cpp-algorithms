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

    ASSERT(heap.getMax() == 35);
}