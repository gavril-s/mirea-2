#ifndef LIST_STACK_H
#define LIST_STACK_H

#include <iostream>
#include "list.h"

class list_stack
{
private:
    list stack;

public:
    list_stack();
    bool is_empty();
    int top();
    void push(int value);
    int pop();
    void clear();
};

#endif