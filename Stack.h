#ifndef STACK_H
#define STACK_H

#include "Item.h"
#include "List.h"
#include <stdbool.h>

// typedef struct node {
//   Item item;
//   struct node *next;
// } Node;

typedef struct {
  Node *top;
  int size;
} Stack;

bool InitializeStack(Stack *pstack);
Item* Pop(Stack *pstack, Item *pitem);
bool Push(Stack *pstack, Item *pitem);
const Item *GetTop(Stack *pstack);
bool StackIsEmpty(Stack *pstack);
void EmptyStack(Stack *pstack);

#endif