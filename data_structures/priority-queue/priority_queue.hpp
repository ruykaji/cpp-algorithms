#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include <cstdint>
#include <vector>

template <class T>
class PriorityQueue {
    std::vector<std::pair<T, int32_t>> m_heap {};

public:
    PriorityQueue() = default;
    ~PriorityQueue() = default;

    PriorityQueue(const PriorityQueue&) = delete;
    PriorityQueue& operator=(const PriorityQueue&) = delete;

    void insert(const T& t_value, const int32_t& t_priority)
    {
        m_heap.emplace_back(std::pair<T, int32_t>(t_value, t_priority));

        if (m_heap.size() > 1) {
            for (std::size_t i = m_heap.size() - 1; i > 0; i = (i - 1) / 2) {
                if (m_heap[i].second < m_heap[(i - 1) / 2].second) {
                    std::iter_swap(m_heap.begin() + i, m_heap.begin() + (i - 1) / 2);
                }
            }
        }
    }

    T pop()
    {
        T root = m_heap.front().first;

        m_heap.erase(m_heap.begin());
        m_heap.insert(m_heap.begin(), m_heap.back());
        m_heap.pop_back();

        auto size = m_heap.size();

        for (std::size_t i = 1; i < size;) {
            if (i == size - 1 || m_heap[i].second < m_heap[i + 1].second) {
                if (m_heap[i].second < m_heap[(i - 1) / 2].second) {
                    std::iter_swap(m_heap.begin() + i, m_heap.begin() + (i - 1) / 2);
                    i = 2 * i + 1;
                } else {
                    break;
                }

            } else {
                if (m_heap[i + 1].second < m_heap[(i - 1) / 2].second) {
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
        return m_heap.front().first;
    }

    inline bool operator==(const std::vector<T>& t_right)
    {
        if (m_heap.size() != t_right.size()) {
            return false;
        }

        for (std::size_t i = 0; i < m_heap.size(); ++i) {
            if (m_heap[i].first != t_right[i]) {
                return false;
            }
        }

        return true;
    }
};

#endif