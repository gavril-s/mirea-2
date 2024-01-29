#include "list_stack.h"

list_stack::list_stack()
{
    stack = list();
}

bool list_stack::is_empty()
{
    return stack.size == 0;
}

int list_stack::top()
{
    if (!is_empty())
    {
        return stack.last->value;
    }
    else
    {
        std::cerr << "top() : stack is empty\n";
        throw "top() : stack is empty";
    }
}

void list_stack::push(int value)
{
    stack.insert_after(stack.last, value);
}

int list_stack::pop()
{
    if (!is_empty())
    {
        int res = stack.last->value;
        stack.remove(stack.last);
        return res;
    }
    else
    {
        std::cerr << "pop() : stack is empty\n";
        throw "pop() : stack is empty";
    }
}

void list_stack::clear()
{
    stack = list();
}