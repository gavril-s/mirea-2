#ifndef DOUBLE_STACK_H
#define DOUBLE_STACK_H

#include <iostream>

#define DOUBLE_STACK_SIZE 1000

enum side
{
    left = 0,
    right = 1
};

class double_stack
{
private:
    int storage[DOUBLE_STACK_SIZE];
    int left_stack_last;
    int right_stack_last;

public:
    double_stack();
    bool is_empty(side stack);
    int top(side stack);
    void push(side stack, int value);
    int pop(side stack);
    void clear(side stack);
};

#endif