#include <gtest/gtest.h>

#include "doubly_linked_list.hpp"

TEST(CPP_Doubly_Linked_List, Empty_Constructor_And_Destructor)
{
    DoublyLinkedList<int32_t> list {};

    SUCCEED();
}

TEST(CPP_Doubly_Linked_List, Append)
{
    DoublyLinkedList<int32_t> list {};

    for (int32_t i = 0; i < 100; ++i) {
        list.append(i);

        EXPECT_EQ(*list.tail(), i);
    }

    EXPECT_EQ(*list.head(), 0);
    EXPECT_EQ(*list.tail(), 99);
    EXPECT_EQ(list.size(), 100);
}

TEST(CPP_Doubly_Linked_List, Prepend)
{
    DoublyLinkedList<int32_t> list {};

    for (int32_t i = 0; i < 100; ++i) {
        list.prepend(i);

        EXPECT_EQ(*list.head(), i);
    }

    EXPECT_EQ(*list.head(), 99);
    EXPECT_EQ(*list.tail(), 0);
    EXPECT_EQ(list.size(), 100);
}

TEST(CPP_Doubly_Linked_List, Insert)
{
    DoublyLinkedList<int32_t> list {};

    list.insert(200, 0);
    EXPECT_EQ(*list.head(), 200);
    EXPECT_EQ(*list.tail(), 200);

    for (int32_t i = 0; i < 100; ++i) {
        list.append(i);
    }

    EXPECT_EQ(list.size(), 101);
}

TEST(CPP_Doubly_Linked_List, Pop_Head)
{
    DoublyLinkedList<int32_t> list {};

    for (int32_t i = 0; i < 100; ++i) {
        list.append(i);
    }

    int32_t head_value = list.pop_head();

    EXPECT_EQ(head_value, 0);
    EXPECT_EQ(list.size(), 99);
}

TEST(CPP_Doubly_Linked_List, Pop_Tail)
{
    DoublyLinkedList<int32_t> list {};

    for (int32_t i = 0; i < 100; ++i) {
        list.append(i);
    }

    int32_t tail_value = list.pop_tail();

    EXPECT_EQ(tail_value, 99);
    EXPECT_EQ(list.size(), 99);
}

TEST(CPP_Doubly_Linked_List, Erase)
{
    DoublyLinkedList<int32_t> list {};

    EXPECT_THROW(list.erase(0), std::runtime_error);

    for (int32_t i = 0; i < 100; ++i) {
        list.append(i);
    }

    list.erase(0);
    EXPECT_EQ(*list.head(), 1);
    EXPECT_EQ(list.size(), 99);

    list.erase(list.size() - 1);
    EXPECT_EQ(*list.tail(), 98);
    EXPECT_EQ(list.size(), 98);
}

TEST(CPP_Doubly_Linked_List, Get)
{
    DoublyLinkedList<int32_t> list {};

    for (int32_t i = 0; i < 100; ++i) {
        list.append(i);
    }

    EXPECT_TRUE(list.get(50));
    EXPECT_EQ(*list.get(50), 50);
}

TEST(CPP_Doubly_Linked_List, Set)
{
    DoublyLinkedList<int32_t> list {};

    for (int32_t i = 0; i < 100; ++i) {
        list.append(i);
    }

    list.set(50, 1000);

    EXPECT_TRUE(list.get(50));
    EXPECT_EQ(*list.get(50), 1000);
}

TEST(CPP_Doubly_Linked_List, Find)
{
    DoublyLinkedList<int32_t> list {};

    for (int32_t i = 0; i < 100; ++i) {
        list.append(i);
    }

    auto itr = list.find(23);

    EXPECT_TRUE(itr);
    EXPECT_EQ(*itr, 23);
}

TEST(CPP_Doubly_Linked_List, Traversal_Forward)
{
    DoublyLinkedList<int32_t> list {};

    for (int32_t i = 0; i < 100; ++i) {
        list.append(i);
    }

    int32_t numeric_itr = 0;
    auto list_itr = list.head();

    while (list_itr) {
        EXPECT_EQ(*list_itr, numeric_itr);

        ++numeric_itr;
        ++list_itr;
    }
}

TEST(CPP_Doubly_Linked_List, Traversal_backward)
{
    DoublyLinkedList<int32_t> list {};

    for (int32_t i = 0; i < 100; ++i) {
        list.append(i);
    }

    int32_t numeric_itr = list.size() - 1;
    auto list_itr = list.tail();

    while (list_itr) {
        EXPECT_EQ(*list_itr, numeric_itr);

        --numeric_itr;
        --list_itr;
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}