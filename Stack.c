#include "Stack.h"
#include <stdlib.h>

bool InitializeStack(Stack *pstack) {
  pstack->size = 0;
  pstack->top = NULL;
  return true;
}

Item *Pop(Stack *pstack, Item *pitem) {
  if (StackIsEmpty(pstack))
    return NULL;
  pstack->size--;
  *pitem = pstack->top->item;
  Node *temp = pstack->top;
  pstack->top = pstack->top->next;
  free(temp);
  return pitem;
}

bool Push(Stack *pstack, Item *pitem) {
  Node *new;
  if ((new = (Node *)malloc(sizeof(Node))) == NULL)
    return false;
  pstack->size++;
  new->item = *pitem;
  new->next = pstack->top;
  pstack->top = new;
  return true;
}

const Item *GetTop(Stack *pstack) { return &pstack->top->item; }

bool StackIsEmpty(Stack *pstack) { return (pstack->size == 0) ? true : false; }

void EmptyStack(Stack *pstack) {
  Node *temp;
  while (!StackIsEmpty(pstack)) {
    temp = pstack->top;
    pstack->top = pstack->top->next;
    free(temp);
  }
}