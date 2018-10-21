#ifndef ITEM_H
#define ITEM_H

enum Item_Type { Item_Int, Item_Float, Item_Operator };

typedef struct {
  enum Item_Type type;
  union {
    int Int;
    float Float;
    char Operator;
  } value;
} Item;

#endif