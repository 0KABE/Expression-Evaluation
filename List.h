#ifndef LIST_ADT_H
#define LIST_ADT_H

#include "Item.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct node {
  Item item;
  struct node *next;
} Node;

typedef struct {
  Node *head;
  int length;
} List;

// list
void InitializeList(List *plist);
void EmptyList(List *plist);
bool ListIsEmpty(List *plist);
void CopyList(List *pdest, List *psource);
void TraverseList(List *plist, void (*function)(const Item *pitem));

// item
void AddItem(List *plist, Item *pitem);

// node
Node *MakeNode(List *plist);
void DeleteNode(List *plist, Node **ppnode);

#endif