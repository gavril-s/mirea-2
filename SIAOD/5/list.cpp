#include "list.h"

list_node::list_node()
{
    value = 0;
    next = nullptr;
}

list_node::list_node(double value)
{
    this->value = value;
    next = nullptr;
}

list::list()
{
    first = nullptr;
    last = nullptr;
    size = 0;
}

list::~list()
{
    list_node* current = first;
    while (current != nullptr)
    {
        list_node* next_node = current->next;
        delete current;
        current = next_node;
    }
}

void list::insert_before(list_node* node, double value)
{
    if (node == nullptr)
    {
        insert_after(last, value);
    }
    else if (node == first)
    {
        list_node* new_node = new list_node(value);
        new_node->next = first;
        first = new_node;
        size++;
    }
    else
    {
        list_node* current = first;
        while (current != nullptr)
        {
            if (current->next == node)
            {
                insert_after(current, value);
                break;
            }
            current = current->next;
        }   
    }
}

void list::insert_after(list_node* node, double value)
{
    if (node == nullptr)
    {
        if (first != nullptr)
        {
            insert_before(first, value);
        }
        else
        {
            first = new list_node(value);
            last = first;
            size++;
        }
    }
    else
    {
        list_node* new_node = new list_node(value);
        new_node->next = node->next;
        node->next = new_node;
        size++;
        if (last == node)
        {
            last = new_node;
        }
    }
}

void list::append(double value)
{
    insert_after(last, value);
}

void list::remove(list_node* node)
{
    if (node == first)
    {
        first = node->next;
        delete node;
    }
    else
    {
        list_node* current = first;
        while (current != nullptr)
        {
            if (current->next == node)
            {
                remove_after(current);
                break;
            }
            current = current->next;
        }
    }
}

void list::remove_after(list_node* node)
{
    if (node != nullptr && node->next != nullptr)
    {
        list_node* to_delete = node->next;
        node->next = to_delete->next;

        if (last == to_delete)
        {
            last = node;
        }

        delete to_delete;
    }
}

void list::print()
{
    list_node* current = first;
    while (current != nullptr)
    {
        std::cout << current->value << ' ';
        current = current->next;
    }
    std::cout << '\n';
}

list_node* list::find_max()
{
    list_node* max = nullptr;
    list_node* current = first;
    while (current != nullptr)
    {
        if (max == nullptr || current->value > max->value)
        {
            max = current;
        }
        current = current->next;
    }

    return max;
}

list_node* list::find_first_negative()
{
    list_node* current = first;
    while (current != nullptr)
    {
        if (current->value < 0)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void list::insert_two_before_last(double value1, double value2)
{
    insert_before(last, value1);
    insert_before(last, value2);
}

void list::delete_first_negative()
{
    list_node* first_negative = find_first_negative();
    remove(first_negative);
}

void list::move_max_to_end()
{
    list_node* max = find_max();
    double max_value = max->value;
    remove(max);
    insert_after(last, max_value);
}