#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <array>
#include <iostream>
#include <memory>
#include <string>

#include "./hash_item.h"

template <class T>
class HashTable
{
    std::unique_ptr<std::shared_ptr<HashItem<T>>[]> m_items{};
    size_t m_size{};
    size_t m_count{};

    unsigned long long hashFunction(const std::string &t_key)
    {
        unsigned long long hash{};

        for (auto c : t_key)
        {
            hash += c;
        }

        return hash % m_size;
    };

public:
    HashTable(const size_t &t_size)
    {
        m_items = std::make_unique<std::shared_ptr<HashItem<T>>[]>(t_size);
        m_size = t_size;
    };

    size_t size()
    {
        return m_count;
    };

    void insert(const std::string &t_key, const T &t_value)
    {
        if (m_count != m_size)
        {
            auto index = hashFunction(t_key);

            if (m_items[index] == nullptr)
            {
                m_items[index] = std::make_shared<HashItem<T>>(t_key, t_value);
            }
            else
            {
                for (auto tmp = m_items[index]; tmp != nullptr; tmp = tmp->next)
                {
                    if (tmp->next == nullptr)
                    {
                        tmp->next = std::make_shared<HashItem<T>>(t_key, t_value);
                        break;
                    }
                }
            }

            ++m_count;
        }
        else
        {
            throw std::runtime_error("Can't insert the element, table is full!\n");
        }
    };

    T &get(const std::string &t_key)
    {
        auto index = hashFunction(t_key);

        if (m_items[index] != nullptr)
        {
            for (auto tmp = m_items[index]; tmp != nullptr; tmp = tmp->next)
            {
                if (tmp->key == t_key)
                {
                    return tmp->value;
                }
            }
        }

        throw std::runtime_error("Can't get element, invalid index!\n");
    };

    void erase(const std::string &t_key)
    {
        auto index = hashFunction(t_key);

        if (m_items[index] != nullptr)
        {
            for (auto tmp = m_items[index]; tmp->next != nullptr; tmp = tmp->next)
            {
                if (tmp->next->key == t_key)
                {
                    tmp->next = tmp->next->next;
                    break;
                }
            }

            --m_count;
        }
        else
        {
            throw std::runtime_error("Can't erase element, invalid index!\n");
        }
    };
};

#endif