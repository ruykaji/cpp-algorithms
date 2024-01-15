#ifndef __DOUBLY_LINKED_LIST_H__
#define __DOUBLY_LINKED_LIST_H__

#include <stdlib.h>

/**
 * @brief Class representing a node for a doubly linked list.
 */
typedef struct Node {
    // Pointer to the previous node in the doubly linked list
    Node* m_ptr_next = NULL;

    // Pointer to the next node in the doubly linked list
    Node* m_ptr_prev = NULL;

    // The value stored in the node
    void* m_ptr_value = NULL;
};

/**
 * @brief Constructor.
 * Initializes a node with pointers to previous and next nodes and a value.
 * @param t_prev A shared pointer to the previous node.
 * @param t_next A shared pointer to the next node.
 * @param t_value The value to be stored in the node.
 * @return Node* Pointer to the new node.
 */
Node* node_constructor(Node* t_prev, Node* t_next, void* t_value)
{
    Node* node_instance = (Node*)malloc(sizeof(Node));

    if (node_instance != NULL) {
        node_instance->m_ptr_prev = t_prev;
        node_instance->m_ptr_next = t_next;
        node_instance->m_ptr_value = t_value;

        return node_instance;
    }

    return NULL;
};

/**
 * @brief Default destructor.
 * @param t_node The node to destruct.
 */
void node_destructor(Node* t_node)
{
    if (t_node != NULL) {
        node_destructor(t_node->m_ptr_prev);
        node_destructor(t_node->m_ptr_next);
        free(t_node->m_ptr_value);
    }
}

/**
 * @brief Sets the previous node.
 * @param t_node The node to modify.
 * @param t_prev The previous node to be set.
 */
void set_prev(Node* t_node, Node* t_prev)
{
    if (t_node != NULL) {
        t_node->m_ptr_prev = t_prev;
    }
}

/**
 * @brief Sets the previous node.
 * @param t_node The node to modify.
 * @param t_next The next node to be set.
 */
void set_next(Node* t_node, Node* t_next)
{
    if (t_node != NULL) {
        t_node->m_ptr_next = t_next;
    }
}

/**
 * @brief Sets the previous node.
 * @param t_node The node to modify.
 * @param t_value The value to be set.
 */
void set_value(Node* t_node, void* t_value)
{
    if (t_node != NULL) {
        t_node->m_ptr_value = t_value;
    }
}

/**
 * @brief Gets a raw pointer to the previous node.
 * @param t_node The node to get from.
 * @return Node* A raw pointer to the previous node.
 */
Node* const get_prev(const Node* t_node)
{
    if (t_node != NULL) {
        return t_node->m_ptr_prev;
    }
}

/**
 * @brief Gets a raw pointer to the next node.
 * @param t_node The node to get from.
 * @return Node* A raw pointer to the next node.
 */
Node* const get_next(const Node* t_node)
{
    if (t_node != NULL) {
        return t_node->m_ptr_next;
    }
}

/**
 * @brief Gets a pointer to the node's value.
 * @param t_node The node to get from.
 * @return void* A raw pointer to the node's value.
 */
void* const get_value(const Node* t_node)
{
    if (t_node != NULL) {
        return t_node->m_ptr_value;
    }
}



#endif
