#pragma once

#include <stdlib.h> 
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct KeyValue KeyValue;
struct KeyValue
{
    const char * key;
    const char * value;
};


typedef struct __StrMap StrMap;
struct __StrMap {
   KeyValue  * items;
   size_t capacity;
   size_t size;
};


int KeyValue_compare(const KeyValue * a, const KeyValue * b);

void StrMap_init(StrMap * self);
void StrMap_deinit(StrMap * self);

size_t  StrMap_size     (StrMap * self);
KeyValue     StrMap_getKV      (StrMap * self, int index);
const char * StrMap_getVal    (StrMap * self, const char * key);


void    StrMap_set      (StrMap * self, int index, KeyValue value);
const char * StrStrMap_setNgetVal    (StrMap * self, const char * key, const char * value);

void    StrMap_removeAt (StrMap * self, int index);
const char * StrStrMap_removeNgetVal (StrMap * self, const char * key);


void    StrMap_add      (StrMap * self, const char * key, const char * value);  // add value and sort, tip: use insertion sort
void    StrMap_remove   (StrMap * self, KeyValue value);  // < O(n), tip: find index and _removeAt()
int     StrMap_indexOf  (StrMap * self, KeyValue value);  // < O(n), tip: use non-linear search method
bool    StrMap_contains (StrMap * self, const char * key);  // < O(n), tip: find index and check it for -1

void    StrMap_clear    (StrMap * self);

StrMap * StrMap_alloc();

int getStrMap_key(StrMap * self);
