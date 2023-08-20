#include "../../include/simple_unit_test.hpp"
#include "./hash_table.h"

TEST_CASE("Should crate an empty hash table.")
{
    auto hashTable = HashTable<int>(10);

    ASSERT(hashTable.size() == 0);
}

TEST_CASE("Should insert new element in hash table.")
{
    auto hashTable = HashTable<int>(10);

    hashTable.insert("element", 100);

    ASSERT(hashTable.size() == 1);
}

TEST_CASE("Should insert new element in hash table and get it back.")
{
    auto hashTable = HashTable<int>(10);

    hashTable.insert("a", 50);
    hashTable.insert("b", 100);
    hashTable.insert("c", 150);

    int result = hashTable.get("b");

    ASSERT(result == 100);
    ASSERT(hashTable.size() == 3);
}

TEST_CASE("Should erase element from hash table and throw error in attempt to get it.")
{
    auto hashTable = HashTable<int>(10);

    hashTable.insert("a", 50);
    hashTable.insert("b", 100);
    hashTable.insert("c", 150);

    hashTable.erase("b");

    ASSERT(hashTable.size() == 2);

    try
    {
        hashTable.get("b");
    }
    catch (const std::exception &e)
    {
        ASSERT(static_cast<std::string>(e.what()) == "Can't get element, invalid index!\n")
    }
}

TEST_CASE("Hash table should deal with collisions.")
{
    auto hashTable = HashTable<int>(10);

    hashTable.insert("a", 50);  // 1
    hashTable.insert("b", 100); // 2
    hashTable.insert("c", 150); // 3
    hashTable.insert("k", 200); // 1
    hashTable.insert("u", 250); // 1

    ASSERT(hashTable.get("a") == 50);
    ASSERT(hashTable.get("k") == 200);
    ASSERT(hashTable.get("u") == 250);
    ASSERT(hashTable.size() == 5);
    
    hashTable.erase("a");

    ASSERT(hashTable.get("k") == 200);
    ASSERT(hashTable.get("u") == 250);

    try
    {
        hashTable.get("a");
    }
    catch (const std::exception &e)
    {
        ASSERT(static_cast<std::string>(e.what()) == "Can't get element, invalid index!\n")
    }

    try
    {
        hashTable.erase("a");
    }
    catch (const std::exception &e)
    {
        ASSERT(static_cast<std::string>(e.what()) == "Can't erase element, invalid index!\n")
    }
}
