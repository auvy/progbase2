#include "strmap.h"

StrMap * StrMap_alloc()
{
    StrMap * new = malloc(sizeof(StrMap));
    StrMap_init(new);
    return new;
}

void StrMap_init(StrMap * self)
{
    self->capacity = 16;
    self->items = malloc(sizeof(KeyValue) * self->capacity);
    self->size = 0;
}
void StrMap_deinit(StrMap * self)
{
    free(self->items);
}

size_t  StrMap_size     (StrMap * self)
{
    return self->size;
}
KeyValue     StrMap_getKV      (StrMap * self, int index)
{
    return self->items[index];
}
const char * StrMap_getVal    (StrMap * self, const char * key)
{
    KeyValue kv;
    kv.key = key;
    int index = StrMap_indexOf(self, kv);
    if (index == -1) 
    {
        abort();
    }
    KeyValue kvf = StrMap_getKV(self, index);
    return kvf.value; 
}

void    StrMap_set      (StrMap * self, int index, KeyValue value)
{
    self->items[index] = value;  
}

const char * StrStrMap_setNgetVal    (StrMap * self, const char * key, const char * value)
{
    KeyValue kv;
    kv.key = key;
    kv.value = value;
    int index = StrMap_indexOf(self, kv);
    if (index == -1) 
    {
        abort();
    }
    KeyValue kvOld = StrMap_getKV(self, index);
    StrMap_set(self, index, kv); 
    return kvOld.value;
}

void    StrMap_removeAt (StrMap * self, int index)
{
    // @todo check index
    for (int i = index; i < self->size - 1; i++)
    {
        self->items[i] = self->items[i + 1];
    }
    self->size -= 1;
}

int KeyValue_compare(const KeyValue * a, const KeyValue * b)
{
    return strcmp(a->key, b->key);
}



void StrMap_realloc(StrMap *self, int newCapacity)
{
    KeyValue *new = realloc((self->items), sizeof(void*) * newCapacity);

    if (new == NULL)
    {
        free(self->items);
        // printf("Reallocation error\n");
        abort();
    }

    self->items = new;
    self->capacity = newCapacity;
    // printf("Reallocated\n");
}



void    StrMap_add      (StrMap * self, const char * key, const char * value)
{
    KeyValue kv;
    kv.key = key;
    kv.value = value;
    
    // self->items[self->size] = kv;
    // self->size += 1;
    for (int i = self->size; i >= 0; i--) 
    {
        if (i == 0) 
        {
            // stop
            self->items[i] = kv;
        }
        else 
        {
            int cmp = KeyValue_compare(&kv, &self->items[i - 1]);
            if (cmp >= 0)
            {
                // stop
                self->items[i] = kv;
                break;
            }
            else 
            {
                self->items[i] = self->items[i - 1];
            }
        }
    } 
    self->size += 1;
    if (self->size == self->capacity)
    {
        // realloc
        int newCapacity = self->capacity + 1;
        StrMap_realloc(self, newCapacity);
    }
}









void    StrMap_remove   (StrMap * self, KeyValue kv)
{
    int index = StrMap_indexOf(self, kv);
    if (index == -1) return;
    for (int i = index; i < self->size - 1; i++)
    {
        self->items[i] = self->items[i + 1]; 
    }
    self->size -= 1; 
}


const char * StrStrMap_removeNgetVal (StrMap * self, const char * key)
{
        KeyValue kv;
    kv.key = key;
    int index = StrMap_indexOf(self, kv);
    if (index == -1) 
    {
        abort();
    }
    KeyValue kvf = StrMap_getKV(self, index);
    StrMap_removeAt(self, index);
    return kvf.value; 
}



int StrMap_indexOf  (StrMap * self, KeyValue kv)
{
    //self->items
    KeyValue * item = bsearch(&kv, self->items, self->size, sizeof(KeyValue), (__compar_fn_t)KeyValue_compare);
    if (item == NULL) return -1;
    return item - self->items; 
}

bool    StrMap_contains (StrMap * self, const char * key)
{
    KeyValue kv;
    kv.key = key;
    return StrMap_indexOf(self, kv) >= 0;
}

void    StrMap_clear    (StrMap * self)
{
    self->size = 0;
}

int getStrMap_key(StrMap * self)
{
    
    KeyValue * kv = &(self->items[2]);
    int keey = atoi(kv->value);
    printf("keyis %d\n", keey);
    return keey;
}