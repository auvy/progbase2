#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

// List module interface
typedef struct __List List;
struct __List
{
    char **array;
    int capacity;
    int length;
};

void List_init(List *self);
void List_deinit(List *self);
void List_add(List *self, char *string, int len);
void List_print(const List *self);

void List_fwrite(List *self);

void List_sort(List *self);