#include "List.h"

void InitializeList(List *plist) {
  plist->head = NULL;
  plist->length = 0;
}

void AddItem(List *plist, Item *pitem) {
  Node *new = MakeNode(plist);
  new->item = *pitem;
  new->next = NULL;
}

bool ListIsEmpty(List *plist) { return (plist->length == 0) ? true : false; }

void EmptyList(List *plist) {
  while (!ListIsEmpty(plist)) {
    DeleteNode(plist, &plist->head);
  }
}

Node *MakeNode(List *plist) {
  plist->length++;
  Node **temp;
  for (temp = &plist->head; *temp; temp = &(*temp)->next)
    ;
  *temp = (Node *)malloc(sizeof(Node));
  return *temp;
}

void DeleteNode(List *plist, Node **ppnode) {
  plist->length--;
  Node *temp = *ppnode;
  *ppnode = (*ppnode)->next;
  free(temp);
}

void TraverseList(List *plist, void (*function)(const Item *pitem)) {
  for (Node *pt = plist->head; pt; pt = pt->next)
    function(&pt->item);
}