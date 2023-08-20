#define SIMPLE_UNIT_TEST

#include "../../include/simple_unit_test.hpp"
#include "./doubly_linked_list.h"

TEST_CASE("List head and tail should be nullptr on right after creation.")
{
    DoublyLinkedList<int> list;

    ASSERT(list.begin() == nullptr);
    ASSERT(list.end() == nullptr);
}

TEST_CASE("Headers previous node and tails next node should be nullptr.")
{
    DoublyLinkedList<int> list;

    list.prepend(0);
    list.prepend(1);

    ASSERT(list.begin()->getPrev() == nullptr);
    ASSERT(list.end()->getNext() == nullptr);
}

TEST_CASE("Should prepend node to a list.")
{
    DoublyLinkedList<int> list;

    for (int i = 0; i < 5; i++)
    {
        list.prepend(i);
    }

    int itr = 4;

    for (auto i = list.begin(); i != nullptr; i = i->getNext(), itr--)
    {
        if (i->getValue() != itr)
        {
            ASSERT(false);
            break;
        }
    }
}

TEST_CASE("Should append node to a list.")
{
    DoublyLinkedList<int> list;

    for (int i = 0; i < 5; i++)
    {
        list.append(i);
    }

    int itr = 0;

    for (auto i = list.begin(); i != nullptr; i = i->getNext(), itr++)
    {
        if (i->getValue() != itr)
        {
            ASSERT(false);
            break;
        }
    }
}

TEST_CASE("Should insert node to a list.")
{
    DoublyLinkedList<int> list;

    list.insert(0, 0);

    ASSERT(list.begin() != nullptr && list.begin()->getValue() == 0);
    ASSERT(list.end() != nullptr && list.end()->getValue() == 0);

    list.append(1);
    list.append(2);

    list.insert(10, 0);

    ASSERT(list.begin()->getValue() == 10);

    list.insert(20, 1);

    ASSERT(list.begin()->getNext()->getValue() == 20);

    list.insert(30, 4);

    ASSERT(list.end()->getPrev()->getValue() == 30);
}

TEST_CASE("Should pop head of a list.")
{
    DoublyLinkedList<int> list;

    list.append(0);
    list.append(1);
    list.append(2);

    list.pop_front();

    ASSERT(list.begin()->getPrev() == nullptr);
    ASSERT(list.begin()->getValue() == 1);
    ASSERT(list.begin()->getNext()->getValue() == 2);

    list.pop_front();
    list.pop_front();

    ASSERT(list.begin() == nullptr);
    ASSERT(list.end() == nullptr);
}

TEST_CASE("Should pop tail of a list.")
{
    DoublyLinkedList<int> list;

    list.append(0);
    list.append(1);
    list.append(2);

    list.pop_back();

    ASSERT(list.end()->getNext() == nullptr);
    ASSERT(list.end()->getValue() == 1);
    ASSERT(list.end()->getPrev()->getValue() == 0);

    list.pop_back();
    list.pop_back();

    ASSERT(list.begin() == nullptr);
    ASSERT(list.end() == nullptr);
}

TEST_CASE("Should erase node from a list.")
{
    DoublyLinkedList<int> list;

    list.append(0);
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);

    list.erase(0);

    ASSERT(list.begin()->getValue() == 1);

    list.erase(4);

    ASSERT(list.end()->getValue() == 4);

    list.erase(2);

    ASSERT(list.end()->getPrev()->getValue() == 2);
}

TEST_CASE("Should fully clear a list.")
{
    DoublyLinkedList<int> list;

    list.append(0);
    list.append(1);
    list.append(2);
    list.append(3);

    list.clear();

    ASSERT(list.begin() == nullptr);
    ASSERT(list.end() == nullptr);
}

TEST_CASE("Should return correct size of a list.")
{
    DoublyLinkedList<int> list;

    ASSERT(list.size() == 0);

    for (int i = 0; i < 100; i++)
    {
        list.append(i);
    }

    ASSERT(list.size() == 100);
}

TEST_CASE("Should find node in list by value.")
{
    DoublyLinkedList<int> list;

    for (int i = 0; i < 10; i++)
    {
        list.append(i);
    }

    ASSERT(list.findByValue(5)->getValue() == 5);
    ASSERT(list.findByValue(100) == nullptr);
}

TEST_CASE("Should find node in list by raw index.")
{
    DoublyLinkedList<int> list;

    for (int i = 0; i < 10; i++)
    {
        list.append(i);
    }

    ASSERT(list.findByRawIndex(5)->getValue() == 5);
    ASSERT(list.findByValue(100) == nullptr);
}
