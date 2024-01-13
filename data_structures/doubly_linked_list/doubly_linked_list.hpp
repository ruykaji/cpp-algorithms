#ifndef __DOUBLY_LINKED_LIST_H__
#define __DOUBLY_LINKED_LIST_H__

#include <memory>
#include <stdexcept>

template <typename T>
class DoublyLinkedList {
    /**
     * @brief Class representing a node for a doubly linked list.
     */
    class Node {
    public:
        /**
         * @brief Constructor.
         * Initializes a node with pointers to previous and next nodes and a value.
         * @param t_prev A shared pointer to the previous node.
         * @param t_next A shared pointer to the next node.
         * @param t_value The value to be stored in the node.
         */
        explicit Node(const std::shared_ptr<Node>& t_prev, const std::shared_ptr<Node>& t_next, const T& t_value)
            : m_ptr_prev(t_prev)
            , m_ptr_next(t_next)
            , m_value(t_value) {};

        // Default constructor
        Node() = default;

        // Default destructor
        ~Node() = default;

        /**
         * @brief Sets the next node.
         * @param t_node The node to be set.
         */
        inline void set_next(const std::shared_ptr<Node>& t_node) { m_ptr_next = t_node; };

        /**
         * @brief Sets the previous node.
         * @param t_node The node to be set.
         */
        inline void set_prev(const std::shared_ptr<Node>& t_node) { m_ptr_prev = t_node; };

        /**
         * @brief Sets the value of the node.
         * @param t_value The value to be set.
         */
        inline void set_value(const T& t_value) { m_value = t_value; };

        /**
         * @brief Gets a shared pointer to the previous node.
         * @return A shared pointer to the previous node.
         */
        inline std::shared_ptr<Node> get_prev() const { return m_ptr_prev; };

        /**
         * @brief Gets a shared pointer to the next node.
         * @return A shared pointer to the next node.
         */
        inline std::shared_ptr<Node> get_next() const { return m_ptr_next; };

        /**
         * @brief Gets the value of the node.
         * @return The value stored in the node.
         */
        inline T get_value() { return m_value; };

    private:
        // Pointer to the previous node in the doubly linked list
        std::shared_ptr<Node> m_ptr_prev {};

        // Pointer to the next node in the doubly linked list
        std::shared_ptr<Node> m_ptr_next {};

        // The value stored in the node
        T m_value {};
    };

public:
    /**
     * @brief Class representing an iterator for a doubly linked list.
     * This iterator allows traversal through a linked list, supporting both forward and backward traversal.
     */
    class Iterator {
    public:
        /**
         * @brief Constructs an iterator starting at the given node.
         * @param t_head Shared pointer to the starting node of the iterator.
         */
        Iterator(const std::shared_ptr<Node>& t_head)
            : m_node(t_head) {};

        // Default destructor
        ~Iterator() = default;

        /**
         * @brief Get method to access the underlying node.
         * Retrieves the current node that the iterator is pointing to.
         * @return std::shared_ptr<Node> A shared pointer to the current node.
         */
        inline constexpr std::shared_ptr<Node> get() const { return m_node; };

        /**
         * @brief Prefix increment operator.
         * Moves the iterator to the next node in the list.
         * @throws std::runtime_error if the next node is nullptr.
         * @return Iterator& Reference to the updated iterator.
         */
        Iterator& operator++()
        {
            if (!m_node->get_next()) {
                throw std::runtime_error("Cannot increment iterator, next node is null.");
            }

            m_node = const_cast<std::shared_ptr<Node>>(m_node->get_next());
            return *this;
        };

        /**
         * @brief Postfix increment operator.
         * Moves the iterator to the next node and returns an iterator to the current node.
         * @throws std::runtime_error if the next node is nullptr.
         * @return Iterator Copy of the iterator before increment.
         */
        Iterator operator++(int)
        {
            if (!m_node->get_next()) {
                throw std::runtime_error("Cannot increment iterator, next node is null.");
            }

            Iterator tmp_itr = *this;
            m_node = const_cast<std::shared_ptr<Node>>(m_node->get_next());
            return tmp_itr;
        }

        /**
         * @brief Prefix decrement operator.
         * Moves the iterator to the previous node in the list.
         * @throws std::runtime_error if the previous node is nullptr.
         * @return Iterator& Reference to the updated iterator.
         */
        Iterator& operator--()
        {
            if (!m_node->get_prev()) {
                throw std::runtime_error("Cannot decrement iterator, previous node is null.");
            }

            m_node = const_cast<std::shared_ptr<Node>>(m_node->get_prev());
            return *this;
        };

        /**
         * @brief Postfix decrement operator.
         * Moves the iterator to the previous node and returns an iterator to the current node.
         * @throws std::runtime_error if the previous node is nullptr.
         * @return Iterator Copy of the iterator before decrement.
         */
        Iterator operator--(int)
        {
            if (!m_node->get_prev()) {
                throw std::runtime_error("Cannot decrement iterator, previous node is null.");
            }

            Iterator tmp_itr = *this;
            m_node = const_cast<std::shared_ptr<Node>>(m_node->get_prev());
            return tmp_itr;
        }

        /**
         * @brief Dereference operator.
         * Returns a reference to the value of the node at the iterator's current position.
         * @return T& Reference to the node's value.
         */
        T& operator*() { return m_node->get_value(); };

        /**
         * @brief Bool conversion operator.
         * Converts the iterator to a boolean value to check if the iterator is in a valid state.
         * This is commonly used to check if the iterator has reached the end of a data structure or is pointing to a valid element.
         * @return bool Returns true if the iterator is pointing to a valid node, false otherwise.
         */
        operator bool() const { return static_cast<bool>(m_node); };

    private:
        // Pointer to the current node in the list.
        std::shared_ptr<Node> m_node {};
    };

    /**
     * @brief Default constructor.
     * Initializes an empty doubly linked list.
     */
    DoublyLinkedList() = default;

    /**
     * @brief Destructor.
     * Clears all the elements in the doubly linked list.
     */
    ~DoublyLinkedList() { clear(); };

    /**
     * @brief Appends a new element at the end of the list.
     * @param t_value The value to append.
     */
    inline void append(const T& t_value)
    {
        auto ptr_new_tail = std::make_shared<Node>(m_ptr_tail, nullptr, t_value);

        if (!m_ptr_tail) {
            m_ptr_tail = std::move(ptr_new_tail);
            m_ptr_head = m_ptr_tail;
        } else {
            m_ptr_tail->set_next(ptr_new_tail);
            m_ptr_tail = std::move(ptr_new_tail);
        }

        ++m_size;
    }

    /**
     * @brief Prepends a new element at the beginning of the list.
     * @param t_value The value to prepend.
     */
    inline void prepend(const T& t_value)
    {
        auto ptr_new_head = std::make_shared<Node>(nullptr, m_ptr_head, t_value);

        if (!m_ptr_head) {
            m_ptr_head = std::move(ptr_new_head);
            m_ptr_tail = m_ptr_head;
        } else {
            m_ptr_head->set_prev(ptr_new_head);
            m_ptr_head = std::move(ptr_new_head);
        }

        ++m_size;
    }

    /**
     * @brief Inserts a new element at the specified index.
     * @param t_value The value to insert.
     * @param t_index The index where the new element should be inserted.
     */
    inline void insert(const T& t_value, const std::size_t& t_index)
    {
        if (!m_ptr_head) {
            return append(t_value);
        }

        std::size_t itr {};

        for (auto i = m_ptr_head; i != nullptr; i = i->get_next()) {
            if (itr == t_index) {
                if (!i->get_prev()) {
                    prepend(t_value);
                    break;
                }

                if (!i->get_next()) {
                    append(t_value);
                    break;
                }

                auto ptr_new_node = std::make_shared<Node>(i->get_prev(), i, t_value);

                i->set_prev(ptr_new_node);
                i->get_prev()->set_next(ptr_new_node);
                break;
            };

            ++itr;
        };

        ++m_size;
    };

    /**
     * @brief Removes and returns the element at the head of the list.
     * @throw std::runtime_error If the list is empty.
     * @return T The value of the removed head element.
     */
    inline constexpr T pop_head()
    {
        if (!m_ptr_head) {
            std::runtime_error("Pop operation failed: The list is empty. No elements available for removal.");
        }

        T head_value = m_ptr_head->get_value();
        const auto ptr_new_head = m_ptr_head->get_next();

        if (ptr_new_head) {
            ptr_new_head->set_prev(nullptr);
            m_ptr_head = std::move(ptr_new_head);
        } else {
            m_ptr_head = nullptr;
            m_ptr_tail = nullptr;
        }

        --m_size;

        return head_value;
    }

    /**
     * @brief Removes and returns the element at the tail of the list.
     * @throw std::runtime_error If the list is empty.
     * @return T The value of the removed tail element.
     */
    inline constexpr T pop_tail()
    {
        if (!m_ptr_head) {
            std::runtime_error("Pop operation failed: The list is empty. No elements available for removal.");
        }

        T tail_value = m_ptr_tail->get_value();
        const auto ptr_new_tail = m_ptr_tail->get_prev();

        if (ptr_new_tail) {
            ptr_new_tail->set_next(nullptr);
            m_ptr_tail = std::move(ptr_new_tail);
        } else {
            m_ptr_head = nullptr;
            m_ptr_tail = nullptr;
        }

        --m_size;

        return tail_value;
    }

    /**
     * @brief Erases the element at the specified index.
     * @param t_index The index of the element to erase.
     * @throw std::runtime_error If the list is empty or index is out of bounds.
     */
    inline void erase(const std::size_t& t_index)
    {
        if (!m_ptr_head) {
            std::runtime_error("Erase operation failed: The list is empty. No elements available for removal.");
        }

        std::size_t itr {};

        for (auto i = m_ptr_head; i != nullptr; i = i->get_next()) {
            if (itr == t_index) {
                if (!i->get_prev()) {
                    pop_head();
                    break;
                }

                if (!i->get_next()) {
                    pop_tail();
                    break;
                }

                const auto tmp_prev_node = i->get_prev();
                const auto tmp_next_node = i->get_next();

                tmp_prev_node->set_next(tmp_next_node);
                tmp_next_node->set_prev(tmp_prev_node);
                break;
            }

            ++itr;
        }

        --m_size;
    }

    /**
     * @brief Gets the element at the specified index.
     * @param t_index The index of the element to get.
     * @return Iterator A iterator that points to the specified index.
     */
    inline constexpr Iterator get(const std::size_t& t_index) const
    {
        std::size_t numeric_itr {};
        Iterator node_itr(m_ptr_head);

        while (node_itr && numeric_itr != t_index) {
            ++numeric_itr;
            ++node_itr;
        }

        return node_itr;
    }

    /**
     * @brief Sets the value of the element at the specified index.
     * @param t_index The index of the element to set.
     * @param t_value The value to set.
     * @return Iterator A iterator that points to the modified value.
     */
    inline constexpr Iterator set(const std::size_t& t_index, const T& t_value) const
    {
        std::size_t numeric_itr {};
        Iterator node_itr(m_ptr_head);

        while (node_itr && numeric_itr != t_index) {
            ++numeric_itr;
            ++node_itr;
        }

        if (node_itr) {
            node_itr.get()->set_value(t_value);
        }

        return node_itr;
    }

    /**
     * @brief Finds the first occurrence of the specified value in the list.
     * @param t_value The value to find.
     * @return Iterator A iterator that points to the value, or nullptr if not found.
     */
    inline constexpr Iterator find(const T& t_value) const
    {
        Iterator itr(m_ptr_head);

        while (itr) {
            if (*itr == t_value) {
                return itr;
            }

            ++itr;
        }

        return itr;
    }

    /**
     * @brief Returns the number of elements in the list.
     * @return The size of the list.
     */
    inline constexpr std::size_t size() { return m_size; }

    /**
     * @brief Returns a iterator that point on the head node.
     * @return A iterator on the head node.
     */
    inline constexpr Iterator head() const { return Iterator(m_ptr_head); }

    /**
     * @brief Returns a iterator that point on the tail node.
     * @return A iterator on the tail node.
     */
    inline constexpr Iterator tail() const { return Iterator(m_ptr_tail); }

    /**
     * @brief Clears all elements from the list.
     */
    inline constexpr void clear()
    {
        while (m_ptr_head) {
            pop_head();
        }
    }

private:
    // Size of the list
    std::size_t m_size {};

    // Pointer to the head node
    std::shared_ptr<Node> m_ptr_head {};

    // Pointer to the tail node
    std::shared_ptr<Node> m_ptr_tail {};
};

#endif