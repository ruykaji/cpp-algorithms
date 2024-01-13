#include <gtest/gtest.h>

#include "doubly_linked_list.hpp"

TEST(CPP_Doubly_Linked_List, Create_Empty_List)
{
    DoublyLinkedList<int32_t> list {};
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}