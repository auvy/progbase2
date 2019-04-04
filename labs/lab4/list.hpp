#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

class List
{
    private:
    char **array_;
    int capacity_;
    int length_;
    public:
    List();
    ~List();
    void List_add(char *string, int len);
    void List_print();
    void List_fwrite();
    void List_sort();
    void List_realloc(int newCapacity);
    int List_length();
    char* & operator[](int index);
};