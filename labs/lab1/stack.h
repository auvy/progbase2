#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct __Stack Stack;
struct __Stack
{
    char **array;
    int capacity;
    int length;
};
void Stack_init(Stack *self);
void Stack_deinit(Stack *self);
void Stack_push(Stack *self, char *string, int len);
char * Stack_pop(Stack *self);
char * Stack_peek(Stack *self);
bool Stack_isEmpty(Stack *self);
//
void Stack_print(const Stack *self);