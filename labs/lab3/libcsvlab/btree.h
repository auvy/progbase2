#pragma once

#include "strmap.h"
#include "addon.h"
#include "strmap.h"
#include <stdio.h>

typedef struct __BinTree BinTree;
struct __BinTree 
{
   int key;
   StrMap * map;      // set on init/alloc
   BinTree * left;  // set to NULL on init
   BinTree * right; // set to NULL on init
};

typedef struct __BSTree BSTree;
struct __BSTree 
{
    BinTree * root;  // a pointer to the root tree node
};

void   BinTree_init     (BinTree * self, StrMap * map);

BinTree * BinTree_alloc (StrMap * map);
void   BinTree_free     (BinTree * self);

void clearBinTree(BinTree * node);

static void printValueOnLevel(BinTree * node, char pos, int depth);
void print(BinTree * node, char pos, int depth);
void printTree(BinTree * root);



void BSTree_init(BSTree * self);
void BSTree_deinit(BSTree * self); 



StrMap SMdelete(BinTree * node, int key, BinTree * parent);
void modifyTreeOnDelete(BinTree * node, BinTree * parent);

void   BSTree_insert   (BSTree * self, StrMap * map);  // add unique
bool   BSTree_lookup   (BSTree * self, int key);  // check for value with a key
StrMap * BSTree_search   (BSTree * self, int key);  // get the value for a key
StrMap BSTree_delete   (BSTree * self, int key);  // delete the value for a key
void   BSTree_clear    (BSTree * self);           // delete all values
void traverseAndDelet(BinTree * node, int N, BSTree * root);
