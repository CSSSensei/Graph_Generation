#ifndef QT_PROJECT_LINKEDLIST_H
#define QT_PROJECT_LINKEDLIST_H
#include <iostream>
#include "IConcatable.h"

template <typename T>
class Node
{
public:
    T data;
    Node<T> *prev;
    Node<T> *next;

    Node(const T &value) : data{value}, prev{nullptr}, next{nullptr} {}
};

template <typename T>
class LinkedList : public IConcatable<T>
{
private:
    Node<T> *head;
    Node<T> *tail;
    size_t size;

    void delete_list()
    {
        Node<T> *current = head;
        while (current)
        {
            Node<T> *next = current->next;
            delete current;
            current = next;
        }

        head = tail = nullptr;
        size = 0;
    }

public:
    LinkedList() : head{nullptr}, tail{nullptr}, size{0} {}

    LinkedList(T *data, size_t size) : head{nullptr}, tail{nullptr}, size{0}
    {
        if (size < 0)
            throw std::invalid_argument("Cannot create LinkedList with negative size");
        if (data == nullptr)
            throw std::invalid_argument("LinkedList Constructor must take not null arguments");
        for (size_t i = 0; i < size; i++)
        {
            this->push_back(data[i]);
        }
    }

    LinkedList(std::initializer_list<T> list) : head{nullptr}, tail{nullptr}, size{0}
    {
        for (const T &value : list)
        {
            push_back(value);
        }
    }

    LinkedList(const LinkedList<T> &other) : head{nullptr}, tail{nullptr}, size{0}
    {
        *this = other;
    }

    LinkedList(LinkedList<T> &&other) : size{std::move(other.size)}, head{std::move(other.head)}, tail{std::move(other.tail)}
    {
        other.size = 0;
        other.head = nullptr;
        other.tail = nullptr;
    }

    ~LinkedList()
    {
        delete_list();
    }

    bool is_empty() const
    {
        return head == nullptr;
    }

    size_t get_size() const override
    {
        return size;
    }

    void push_front(const T &value)
    {
        Node<T> *new_node = new Node<T>(value);

        if (is_empty())
        {
            head = tail = new_node;
        }
        else
        {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }

        size++;
    }

    void push_back(const T &value) override
    {
        if (is_empty())
        {
            push_front(value);
            return;
        }

        Node<T> *new_node = new Node<T>(value);

        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
        size++;
    }

    T &front()
    {
        if (is_empty())
            throw std::out_of_range("List is empty");

        return head->data;
    }

    const T &front() const
    {
        if (is_empty())
            throw std::out_of_range("List is empty");

        return head->data;
    }

    T &back()
    {
        if (is_empty())
            throw std::out_of_range("List is empty");

        return tail->data;
    }

    const T &back() const
    {
        if (is_empty())
            throw std::out_of_range("List is empty");

        return tail->data;
    }

    void pop_front()
    {
        if (is_empty())
            throw std::out_of_range("List is empty");

        Node<T> *temp = head;
        if (size == 1)
        {
            head = tail = nullptr;
        }
        else
        {
            head = head->next;
            head->prev = nullptr;
        }

        delete temp;
        size--;
    }

    void pop_back()
    {
        if (is_empty())
            throw std::out_of_range("List is empty");

        Node<T> *temp = tail;
        if (size == 1)
        {
            pop_front();
            return;
        }

        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
        size--;
    }

    T &get(size_t index) override
    {
        if (index < 0 || index >= size)
            throw std::out_of_range("Out of range");
        if (is_empty())
            throw std::out_of_range("List is empty");
        auto it = begin();
        for (size_t i = 0; i < index; i++)
        {
            it++;
        }
        return *it;
    }
    void erase(size_t index)
    {
        if (index >= size)
        {
            throw std::out_of_range("Index out of range");
        }

        Node<T> *current = head;
        for (size_t i = 0; i < index; ++i){
            current = current->next;
        }

        if (current->prev){
            current->prev->next = current->next;
        }else{
            head = current->next;
        }

        if (current->next){
            current->next->prev = current->prev;
        }else{
            tail = current->prev;
        }

        delete current;
        --size;
    }

    void clear()
    {
        delete_list();
    }

    LinkedList<T> &operator=(const LinkedList<T> &other)
    {
        delete_list();
        Node<T> *other_cur = other.head;
        while (other_cur)
        {
            push_back(other_cur->data);
            other_cur = other_cur->next;
        }
        return *this;
    }
    LinkedList<T> &operator+=(LinkedList<T> &other)
    {
        return *concat(&other);
    }

    LinkedList<T> &move_to_end(LinkedList<T> &other)
    {
        other.head->prev = tail;

        tail->next = std::move(other.head);
        other.head = nullptr;

        tail = std::move(other.tail);
        other.tail = nullptr;
        size += other.size;
        other.size = 0;

        return *this;
    }

    class Iterator
    {
    private:
        Node<T> *cur;

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;

        Iterator(Node<T> *node) : cur(node) {}

        Iterator &operator++()
        {
            if (cur != nullptr)
            {
                cur = cur->next;
            }
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        Iterator &operator--()
        {
            if (cur != nullptr)
            {
                cur = cur->prev;
            }
            return *this;
        }

        Iterator operator--(int)
        {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator!=(const Iterator &other) const
        {
            return cur != other.cur;
        }

        bool operator==(const Iterator &other) const
        {
            return cur == other.cur;
        }

        reference operator*()
        {
            if (cur == nullptr)
                throw std::runtime_error("Iterator refers to null");
            return cur->data;
        }

        pointer operator->()
        {
            return &cur->data;
        }
    };

    class ConstIterator {
    private:
        const Node<T>* cur;
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = const T*;
        using reference = const T&;

        ConstIterator(const Node<T>* node) : cur(node) {}

        reference operator*() const {
            if (cur == nullptr)
                throw std::runtime_error("Iterator refers to null");
            return cur->data;
        }

        ConstIterator& operator++() {
            cur = cur->next;
            return *this;
        }

        ConstIterator operator++(int) {
            ConstIterator tmp = *this;
            cur = cur->next;
            return tmp;
        }

        bool operator==(const ConstIterator& other) const {
            return cur == other.cur;
        }

        bool operator!=(const ConstIterator& other) const {
            return cur != other.cur;
        }

        pointer operator->() const {
            return &cur->data;
        }
    };

    Iterator begin()
    {
        return Iterator(head);
    }

    Iterator end()
    {
        if (tail == nullptr)
        {
            return Iterator(nullptr);
        }

        return Iterator(tail->next);
    }

    ConstIterator begin() const
    {
        return ConstIterator(head);
    }

    ConstIterator end() const
    {
        if (tail == nullptr)
        {
            return ConstIterator(nullptr);
        }
        return ConstIterator(tail->next);
    }
};
#endif //QT_PROJECT_LINKEDLIST_H
