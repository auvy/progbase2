// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <assert.h>
// #include <stdbool.h>
#include "list.h"

void List_init(List *self)
{
    self->length = 0;
    self->capacity = 2;
    self->array = malloc(self->capacity * sizeof(char*));
    if (self->array == NULL)
    {
        fprintf(stderr, "Allocation error");
        abort();
    }
}

void List_deinit(List *self)
{
    for(int i = 0; i < self->length; i++)
    {
        free(self->array[i]);
    }
    free(self->array);
}

static void List_realloc(List *self, int newCapacity)
{
    char **newArray = realloc((self->array), sizeof(char*) * newCapacity);

    if (newArray == NULL)
    {
        free(self->array);
        fprintf(stderr, "Reallocation error");
        abort();
    }

    self->array = newArray;
    self->capacity = newCapacity;
    // printf("Reallocated\n");
}

void List_add(List *self, char *string, int len)
{
    self->array[self->length] = malloc((len + 1) * sizeof(char));

    strcpy(self->array[self->length], string);

    //
    self->length += 1;
    //
    if (self->length == self->capacity)
    {
        // realloc
        int newCapacity = self->capacity + 1;
        List_realloc(self, newCapacity);
    }
}

void List_print(const List *self)
{
    printf("Printing list: \n\n");
    for(int i = 0; i < self->length; i++)
    {
        // printf("%d\n", (int)strlen(self->array[i]));
        printf("%s\n", self->array[i]);
    }
    puts("");
}

void List_sort(List *self)
{
    printf("Sorting...\n");
    char *bufpoint;

    for(int i = 0; i < self->length; i++)
    {
        if((strstr(self->array[i], " the ") != NULL))
        {
            bufpoint = self->array[i];

            for(int j = i; j < self->length; j++)
            {
                if((strstr(self->array[j], " the ") == NULL))
                {
                    self->array[i] = self->array[j];
                    self->array[j] = bufpoint;
                    break;
                }
            }
        }
    }
}

void List_fwrite(List *self)
{
    FILE *file;

    char buf[256] = {'\0'};

    int bufc = 0;

    file = fopen("data.txt", "r");

    while (fgets(buf, 256, file))
    {
        while (buf[bufc] != '\0')
        {
            if (buf[bufc] == '\n') buf[bufc] = '\0';
            bufc++;
        }

        List_add(self, buf, bufc);

        for(int i = 0; i < bufc; i++)
        {
            buf[i] = '\0';
        }
        bufc = 0;
    }

    fclose(file);
}
