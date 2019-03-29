#include "btree.h"

void   BinTree_init     (BinTree * self, StrMap * map)
{
    self->key = getStrMap_key(map); 
    self->map = map;
    self->left = NULL; 
    self->right = NULL;
}


BinTree * BinTree_alloc (StrMap * map) 
{
    BinTree * self = malloc(sizeof(BinTree));
    BinTree_init(self, map); 
    return self;
}
void   BinTree_free     (BinTree * self)
{
    free(self); 
}



void clearBinTree(BinTree * node)
{
    if (node == NULL) return;
    clearBinTree(node->left);
    clearBinTree(node->right);
    BinTree_free(node);
}

static void printValueOnLevel(BinTree * node, char pos, int depth)
{
   for (int i = 0; i < depth; i++) {
       printf("....");
   }
   printf("%c: ", pos);

   if (node == NULL) {
       printf("(null)\n");
   } else {
        printf("[%d]: ",node->key);
        for(int i = 0; i < 6; i++)
        {
            printf("%s - ", node->map->items[i].value);
        }
        printf("\n");
   }
}

void print(BinTree * node, char pos, int depth)
{
    bool isNotNull = (node != NULL) && (node->left != NULL || node->right != NULL);
    if (isNotNull) print(node->right, 'R', depth + 1);
    printValueOnLevel(node, pos, depth);
    if (isNotNull) print(node->left, 'L', depth + 1);
}

void printTree(BinTree * root)
{
    printf("\nPRINTING TREE\n");
    print(root, '+', 0);
}

void BSTree_init(BSTree * self)
{
    self->root = NULL; 
}
void BSTree_deinit(BSTree * self)
{
    BinTree_free(self->root);
}

static void insert(BinTree * node, BinTree * newNode)
{
    if (newNode->key == node->key)
    {
        fprintf(stderr, "`%i` Already exists\n", newNode->key);
        abort(); 
    }
    if (newNode->key < node->key)
    {
        if (node->left == NULL)
        {
            node->left = newNode; 
        }
        else 
        {
            insert(node->left, newNode); 
        }
    } 
    else if (newNode->key > node->key)
    {
        if (node->right == NULL)
        {
            node->right = newNode; 
        }
        else 
        {
            insert(node->right, newNode); 
        }
    }
}

void   BSTree_insert   (BSTree * self, StrMap * map)
{
    BinTree * newNode = BinTree_alloc(map);
    if (self->root == NULL)
    {
        self->root = newNode;
    }
    else 
    {
        insert(self->root, newNode);
    }
}

static bool lookup(BinTree * node, int key) 
{
    if (node == NULL) return false;
    if (node->key == key) return true;
    if (key < node->key) return lookup(node->left, key);
    if (key > node->key) return lookup(node->right, key);
    else return false;
}
 
bool   BSTree_lookup   (BSTree * self, int key)
{
    return lookup(self->root, key);
}

static StrMap * search(BinTree * node, int key) 
{
    if (node == NULL) return NULL; 
    if (node->key == key) return node->map;
    if (key < node->key) return search(node->left, key);
    if (key > node->key) return search(node->right, key);
    else return NULL;
}
  
StrMap *   BSTree_search   (BSTree * self, int key)
{
    return search(self->root, key);
}

static BinTree * searchMin(BinTree * node)
{
    if (node == NULL) return NULL; 
    if (node->left == NULL) return node;
    return searchMin(node->left); 
}


void modifyTreeOnDelete(BinTree * node, BinTree * parent)
{
    if (node->left == NULL && node->right == NULL)
    { 
        // case A
        if (parent->left == node) parent->left = NULL;
        else parent->right = NULL;
    }
    else if (node->left == NULL || node->right == NULL)
    {
        // case B
        BinTree * child = (node->left != NULL) ? node->left : node->right;
        if (parent->left == node) parent->left = child;
        else parent->right = child;
    }
    else 
    {
        // case C 
        BinTree * minNode = searchMin(node->right);
        int minKey = minNode->key;
        StrMap deletedValue = SMdelete(node->right, minKey, parent);
        BinTree * newMin = BinTree_alloc(&deletedValue);
        newMin->left = node->left;
        newMin->right = node->right;
        if (parent->left == node) parent->left = minNode;
        else parent->right = minNode;
        
    }
}

StrMap SMdelete(BinTree * node, int key, BinTree * parent)
{
    if (node == NULL) 
    {
        fprintf(stderr, "`%i` not found\n", key);
        abort();
    }
    if (key < node->key) return SMdelete(node->left, key, node);
    else if (key > node->key) return SMdelete(node->right, key, node);
    else {
        modifyTreeOnDelete(node, parent);
        StrMap old = *node->map;
        BinTree_free(node);  
        return old;
    }
}

StrMap BSTree_delete   (BSTree * self, int key)
{
    BinTree fakeRoot;
    fakeRoot.left = self->root;
    StrMap old = SMdelete(self->root, key, &fakeRoot);
    self->root = fakeRoot.left;
    return old;
}

void traverseAndDelet(BinTree * node, int N, BSTree * root)
{
    if (node == NULL) return;
    traverseAndDelet(node->left, N, root);
    if(atoi(node->map->items[3].value) < N)
    {
        BinTree * next = node->left;
        BinTree * rext = node->right;
        BSTree_delete(root, node->key);
        traverseAndDelet(next, N, root);
        traverseAndDelet(rext, N, root);
        return;
    }
    traverseAndDelet(node->right, N, root);
}

