#include "array_stack.h"

array_stack::array_stack()
{
    top_index = -1;
}

bool array_stack::is_empty()
{
    return top_index < 0;
}

int array_stack::top()
{
    if (!is_empty())
    {
        return stack[top_index];
    }
    else
    {
        std::cerr << "top() : stack is empty\n";
        throw "top() : stack is empty";
    }
}

void array_stack::push(int value)
{
    if (top_index + 1 < MAX_ARRAY_STACK_SIZE)
    {
        top_index++;
        stack[top_index] = value;
    }
    else
    {
        std::cerr << "push() : stack overflow\n";
        throw "push() : stack overflow";
    }
}

int array_stack::pop()
{
    if (!is_empty())
    {
        top_index--;
        return stack[top_index + 1];
    }
    else
    {
        std::cerr << "pop() : stack is empty\n";
        throw "pop() : stack is empty";
    }
}

void array_stack::clear()
{
    top_index = -1;
}