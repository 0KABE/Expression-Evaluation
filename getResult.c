#include "Item.h"
#include "Stack.h"
#include <math.h>

Item getResult(List *plist) {
  Stack stack;
  InitializeStack(&stack);

  Item a;
  Item b;
  Item c;
  for (Node *pt = plist->head; pt; pt = pt->next) {
    if (pt->item.type == Item_Operator) {
      Pop(&stack, &b);
      Pop(&stack, &a);
      switch (pt->item.value.Operator) {
      case '+':
        c.type = (a.type == Item_Float || b.type == Item_Float) ? Item_Float
                                                                : Item_Int;
        if (c.type == Item_Float)
          c.value.Float =
              ((a.type == Item_Float) ? a.value.Float : a.value.Int) +
              ((b.type == Item_Float) ? b.value.Float : b.value.Int);
        else
          c.value.Int = ((a.type == Item_Float) ? a.value.Float : a.value.Int) +
                        ((b.type == Item_Float) ? b.value.Float : b.value.Int);
        Push(&stack, &c);
        break;

      case '-':
        c.type = (a.type == Item_Float || b.type == Item_Float) ? Item_Float
                                                                : Item_Int;
        if (c.type == Item_Float)
          c.value.Float =
              ((a.type == Item_Float) ? a.value.Float : a.value.Int) -
              ((b.type == Item_Float) ? b.value.Float : b.value.Int);
        else
          c.value.Int = ((a.type == Item_Float) ? a.value.Float : a.value.Int) -
                        ((b.type == Item_Float) ? b.value.Float : b.value.Int);
        Push(&stack, &c);
        break;

      case '*':
        c.type = (a.type == Item_Float || b.type == Item_Float) ? Item_Float
                                                                : Item_Int;
        if (c.type == Item_Float)
          c.value.Float =
              ((a.type == Item_Float) ? a.value.Float : a.value.Int) *
              ((b.type == Item_Float) ? b.value.Float : b.value.Int);
        else
          c.value.Int = ((a.type == Item_Float) ? a.value.Float : a.value.Int) *
                        ((b.type == Item_Float) ? b.value.Float : b.value.Int);
        Push(&stack, &c);
        break;

      case '/':
        c.type = ((a.type == Item_Float || b.type == Item_Float) ||
                  a.value.Int % b.value.Int != 0)
                     ? Item_Float
                     : Item_Int;
        if (c.type == Item_Float)
          c.value.Float = a.value.Float / b.value.Float;
        else
          c.value.Int = a.value.Int / b.value.Int;
        Push(&stack, &c);
        break;

      case '^':
        c.type = Item_Float;
        c.value.Float =
            pow((a.type == Item_Float) ? a.value.Float : a.value.Int,
                (b.type == Item_Float) ? b.value.Float : b.value.Int);
        Push(&stack, &c);
        break;
      }
    } else {
      Push(&stack, &pt->item);
    }
  }
  return *Pop(&stack, &c);
}