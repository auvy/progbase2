
#include "list.h"


void    List_init     (List * self)
{
    self->capacity = 2;
    self->length = 0;
    self->items = malloc(sizeof(void *) * self->capacity);
    if (self->items == NULL)
    {
        printf("Allocation error\n");
        abort();
    }
}
void    List_deinit   (List * self)
{
    free(self->items);
}

List *  List_alloc    (void)
{
    List * self = malloc(sizeof(List));
    List_init(self);
    return self;
}

void    List_free     (List * self)
{
    List_deinit(self);
    free(self);
}

void List_realloc(List *self, int newCapacity)
{
    void **new = realloc((self->items), sizeof(void*) * newCapacity);

    if (new == NULL)
    {
        free(self->items);
        fprintf(stderr, "Reallocation error");
        abort();
    }

    self->items = new;
    self->capacity = newCapacity;
    // printf("Reallocated\n");
}


void List_add(List * self, T value)
{
    self->items[self->length] = value;
    self->length += 1;

    if (self->length == self->capacity)
    {
        // realloc
        int newCapacity = self->capacity + 1;
        List_realloc(self, newCapacity);
    }
}



T List_get      (List * self, int index)
{
    return self->items[index]; 
}

size_t  List_size     (List * self)
{
    return self->length;
}

char *createOnHeap(char *str)
{
    char *meme = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(meme, str);
    return meme;
}
