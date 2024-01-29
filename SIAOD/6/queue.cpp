#include "queue.h"

bool queue::empty()
{
    return (elems.size == 0);
}

void queue::push(int value)
{
    elems.insert_after(elems.last, value);
}

int queue::pop()
{
    int ret = elems.first->value;
    elems.remove(elems.first);
    return ret;
}

int queue::size()
{
    return elems.size;
}