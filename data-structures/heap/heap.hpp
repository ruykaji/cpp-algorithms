#ifndef __HEAP_H__
#define __HEAP_H__

#include <algorithm>
#include <vector>

template <class T>
class MaxHeap {
    std::vector<T> m_heap {};

public:
    MaxHeap() = default;
    ~MaxHeap() = default;

    MaxHeap(const MaxHeap&) = delete;
    MaxHeap& operator=(const MaxHeap&) = delete;

    void insert(const T& t_value)
    {
        m_heap.push_back(t_value);

        if (m_heap.size() > 1) {
            for (size_t i = m_heap.size() - 1; i > 0; i = (i - 1) / 2) {
                if (m_heap[(i - 1) / 2] < m_heap[i]) {
                    std::iter_swap(m_heap.begin() + i, m_heap.begin() + (i - 1) / 2);
                }
            }
        }
    }

    T getMax()
    {
        return m_heap.front();
    }
};

#endif