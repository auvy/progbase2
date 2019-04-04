#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

class Stack
{
    private:
    char **array_;
    int capacity_;
    int length_;
    public:
    Stack();
    ~Stack();
    void Stack_push(char *string, int len);
    char *Stack_pop();
    char *Stack_peek();
    bool Stack_isEmpty();
    void Stack_print();
    void Stack_realloc(int newCapacity);
    int Stack_length();
    char* & operator[](int index);
};