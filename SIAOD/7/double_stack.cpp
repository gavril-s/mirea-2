#include "double_stack.h"

double_stack::double_stack()
{
    left_stack_last = -1;
    right_stack_last = DOUBLE_STACK_SIZE;
}

bool double_stack::is_empty(side stack)
{
    if (stack == left)
    {
        return left_stack_last < 0;
    }
    else if (stack == right)
    {
        return right_stack_last >= DOUBLE_STACK_SIZE;
    }
    else
    {
        std::cerr << "Invalid stack parameter\n";
        throw;
    }
}

int double_stack::top(side stack)
{
    if (stack == left)
    {
        if (!(is_empty(stack)))
        {
            return storage[left_stack_last];
        }
        else
        {
            std::cerr << "Stack is empty\n";
            throw;
        }
    }
    else if (stack == right)
    {
        if (!(is_empty(stack)))
        {
            return storage[right_stack_last];
        }
        else
        {
            std::cerr << "Stack is empty\n";
            throw;
        }
    }
    else
    {
        std::cerr << "Invalid stack parameter\n";
        throw;
    }
}

void double_stack::push(side stack, int value)
{
    if (stack == left)
    {
        if (left_stack_last + 1 < right_stack_last)
        {
            left_stack_last++;
            storage[left_stack_last] = value;
        }
        else
        {
            std::cerr << "Stack is full\n";
            throw;
        }
    }
    else if (stack == right)
    {
        if (right_stack_last - 1 > left_stack_last)
        {
            right_stack_last--;
            storage[right_stack_last] = value;
        }
        else
        {
            std::cerr << "Stack is full\n";
            throw;
        }
    }
    else
    {
        std::cerr << "Invalid stack parameter\n";
        throw;
    }
}

int double_stack::pop(side stack)
{
    if (stack == left)
    {
        if (!(is_empty(stack)))
        {
            left_stack_last--;
            return storage[left_stack_last + 1];
        }
        else
        {
            std::cerr << "Stack is empty\n";
            throw;
        }
    }
    else if (stack == right)
    {
        if (!(is_empty(stack)))
        {
            right_stack_last++;
            return storage[right_stack_last - 1];
        }
        else
        {
            std::cerr << "Stack is empty\n";
            throw;
        }
    }
    else
    {
        std::cerr << "Invalid stack parameter\n";
        throw;
    }
}

void double_stack::clear(side stack)
{
    if (stack == left)
    {
        left_stack_last = -1;
    }
    else if (stack == right)
    {
        right_stack_last = DOUBLE_STACK_SIZE;
    }
    else
    {
        std::cerr << "Invalid stack parameter\n";
        throw;
    }
}