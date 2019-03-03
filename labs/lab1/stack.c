#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <progbase.h>
#include <progbase/console.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>

#include "stack.h"

// Stack module implementation
void Stack_init(Stack *self)
{
    self->length = 0;
    self->capacity = 4;
    self->array = malloc(self->capacity * sizeof(char*));
    if (self->array == NULL)
    {
        fprintf(stderr, "Allocation error");
        abort();
    }
}

void Stack_deinit(Stack *self)
{
    for(int i = 0; i < self->length; i++)
    {
        free(self->array[i]);
    }
    free(self->array);
}

static void Stack_realloc(Stack *self, int newCapacity)
{
    char **newArray = realloc(self->array, sizeof(char*) * newCapacity);
    if (newArray == NULL)
    {
        for (int i = 0; i < self->length; i++)
        {
            free(self->array[i]);
        }
        free(self->array);
        fprintf(stderr, "Reallocation error");
        abort();
    }
    self->array = newArray;
    self->capacity = newCapacity;
    // printf("Reallocated");
}

void Stack_push(Stack *self, char *string, int len)
{
    self->array[self->length] = malloc((len + 1) * sizeof(char));

    strcpy(self->array[self->length], string);

    self->length += 1;
    //
    if (self->length == self->capacity)
    {
        // realloc
        int newCapacity = self->capacity + 1;
        Stack_realloc(self, newCapacity);
    }
}

char * Stack_pop(Stack *self)
{
    if (self->length == 0) 
    {
        fprintf(stderr, "Stack underflow");
        abort();
    }

    char *string = self->array[self->length - 1];
    self->length -= 1;
    return string;
}


char * Stack_peek(Stack *self)
{
    if (self->length == 0) 
    {
        fprintf(stderr, "Stack underflow");
        abort();
    }
    char *string = self->array[self->length - 1];
    return string;
}

bool Stack_isEmpty(Stack *self)
{
    return self->length == 0;
}


void Stack_print(const Stack *self)
{
    printf("Printing stack: \n\n");
    for(int i = 0; i < self->length; i++)
    {
        // printf("%d\n", (int)strlen(self->array[i]));
        printf("%s\n", self->array[i]);
    }
    puts("");
}