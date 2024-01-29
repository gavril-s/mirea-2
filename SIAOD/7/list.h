#ifndef LIST_H
#define LIST_H

#include <iostream>

struct list_node
{
    int value;
    list_node* next;

    list_node();
    list_node(int value);
};

struct list
{
    list_node* first;
    list_node* last;
    int size;

    list();
    ~list();

    void insert_before(list_node* node, int value);
    void insert_after(list_node* node, int value);
    void append(int value);
    void remove(list_node* node);
    void remove_after(list_node* node);
    void print();

    list_node* find_max();
    list_node* find_first_negative();

    void insert_two_before_last(int value1, int value2);
    void delete_first_negative();
    void move_max_to_end();
};

#endif