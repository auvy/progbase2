#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <assert.h>

typedef void * T;

typedef struct __List List;
struct  __List
{
    void ** items;
    size_t capacity;
    size_t length;
};


void    List_init     (List * self);
void    List_deinit   (List * self);

List *  List_alloc    (void);
void    List_free     (List * self);

void *  List_get      (List * self, int index);
size_t  List_size     (List * self);


void    List_add      (List * self, void * value);

void List_realloc(List *self, int newCapacity);

char *createOnHeap(char *str);