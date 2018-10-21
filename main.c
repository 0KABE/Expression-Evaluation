#include "List.h"
#include "getExpression.h"
#include <stdio.h>
#include <stdlib.h>

#define EXPRESSION_SIZE 100

void releaseBuffer();
void displayItem(const Item *pitem);
Item getResult(List *plist);

int main(void) {
  List list;
  InitializeList(&list);
  puts("Enter an expression to caculate:");
  int status;
  while ((status = getExpression(&list))) {
    if (status == -1) {
      puts("Input error! Enter it again:");
      EmptyList(&list);
      releaseBuffer();
      continue;
    }
    Item result = getResult(&list);
    if (result.type == Item_Float)
      printf("%.4f", result.value.Float);
    else
      printf("%d", result.value.Int);

    puts("\nSuffix expression:");
    TraverseList(&list, displayItem);
    putchar('\n');
    EmptyList(&list);
  }

  EmptyList(&list);
  system("pause");
  return 0;
}

void displayItem(const Item *pitem) {
  switch (pitem->type) {
  case Item_Int:
    printf(" %d ", pitem->value.Int);
    break;
  case Item_Float:
    printf(" %.5f ", pitem->value.Float);
    break;
  case Item_Operator:
    printf(" %c ", pitem->value.Operator);
    break;
  }
}