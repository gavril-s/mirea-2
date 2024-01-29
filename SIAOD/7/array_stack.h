#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include <iostream>

#define MAX_ARRAY_STACK_SIZE 1000

class array_stack
{
private:
    int stack[MAX_ARRAY_STACK_SIZE];
    int top_index;

public:
    array_stack();
    bool is_empty();
    int top();
    void push(int value);
    int pop();
    void clear();
};

#endif