#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

struct queue
{
    list elems;

    bool empty();
    void push(int value);
    int pop();
    int size();
};

#endif