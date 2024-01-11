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

        if (m_heap.size() >= 1) {
            for (std::size_t i = m_heap.size() - 1; i > 0; i = (i - 1) / 2) {
                if (m_heap[(i - 1) / 2] < m_heap[i]) {
                    std::iter_swap(m_heap.begin() + i, m_heap.begin() + (i - 1) / 2);
                }
            }
        }
    }

    T pop()
    {
        T root = m_heap.front();

        m_heap.erase(m_heap.begin());
        m_heap.insert(m_heap.begin(), m_heap.back());
        m_heap.pop_back();

        auto size = m_heap.size();

        for (std::size_t i = 1; i < size;) {
            if (i == size - 1 || m_heap[i] > m_heap[i + 1]) {
                if (m_heap[i] > m_heap[(i - 1) / 2]) {
                    std::iter_swap(m_heap.begin() + i, m_heap.begin() + (i - 1) / 2);
                    i = 2 * i + 1;
                } else {
                    break;
                }
            } else {
                if (m_heap[i + 1] > m_heap[(i - 1) / 2]) {
                    std::iter_swap(m_heap.begin() + i + 1, m_heap.begin() + (i - 1) / 2);
                    i = 2 * (i + 1) + 1;
                } else {
                    break;
                }
            }
        }

        return root;
    }

    T peek()
    {
        return m_heap.front();
    }

    inline bool operator==(const std::vector<T>& t_right)
    {
        return m_heap == t_right;
    }
};

#endif