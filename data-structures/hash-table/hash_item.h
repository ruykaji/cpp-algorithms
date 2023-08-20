#ifndef HASH_ITEM_H
#define HASH_ITEM_H

#include <string>
#include <memory>

template <class T>
class HashItem
{
public:
    std::shared_ptr<HashItem<T>> next{};
    std::string key{};
    T value{};

    HashItem() = default;
    HashItem(const std::string &t_key, const T &t_value) : key(t_key), value(t_value){};
};

#endif