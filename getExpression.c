#include "getExpression.h"
#include "Stack.h"
#include <ctype.h>

enum getElement_return {
  getElement_Error = -1,
  getElement_Newline,
  getElement_Int,
  getElement_Float,
  getElement_Operator
};

enum charType_return {
  charType_Other,
  charType_Digit,
  charType_Dot,
  charType_Operator
};

// The function return the priority value of the operator
int getPriority(char ch);
// The function get the element from the input buffer
// and store it in the str[]
int getElement(char str[]);
// The function get the character and distinguish the type
int charType(char ch);

int getExpression(List *expression) {
  int ch;
  char element[100];
  if ((ch = getchar()) == 'q') {
    releaseBuffer();
    return 0;
  }

  ungetc(ch, stdin);
  int element_type;
  Item new, temp;
  Stack operator;
  InitializeStack(&operator);
  while ((element_type = getElement(element)) != getElement_Error &&
         element_type != getElement_Newline) {
    int priority;
    switch (element_type) {
    case getElement_Int:
      new.value.Int = atoi(element);
      new.type = Item_Int;
      AddItem(expression, &new);
      break;

    case getElement_Float:
      new.value.Float = atof(element);
      new.type = Item_Float;
      AddItem(expression, &new);
      break;

    case getElement_Operator:
      new.value.Operator = element[0];
      new.type = Item_Operator;
      if (StackIsEmpty(&operator) || new.value.Operator == '(')
        Push(&operator, &new);
      else if (new.value.Operator != ')') {
        priority = getPriority(new.value.Operator);
        while (!StackIsEmpty(&operator) &&
               getPriority(GetTop(&operator)->value.Operator) >= priority)
          AddItem(expression, Pop(&operator, &temp));
        Push(&operator, &new);
      } else {
        Item temp;
        while (GetTop(&operator)->value.Operator != '(')
          AddItem(expression, Pop(&operator, &temp));
        Pop(&operator, &temp);
      }
      break;
    }
  }
  while (!StackIsEmpty(&operator))
    AddItem(expression, Pop(&operator, &temp));

  EmptyStack(&operator);
  if (element_type == getElement_Newline)
    return 1; // successful
  else {
    releaseBuffer();
    return -1; // error
  }
}

void releaseBuffer() { scanf("%*[^\n]%*c"); }

int getElement(char str[]) {
  char ch = getchar();
  if (ch == '\n') // determine whether the character is newline
    return getElement_Newline;

  ungetc(ch, stdin);
  switch (charType(ch)) {
  case charType_Digit:
    scanf("%[0-9.]", str);
    if (strchr(str, '.'))
      return getElement_Float;
    else
      return getElement_Int;

  case charType_Operator:
    scanf("%1[+-*/^()]", str);
    if (strlen(str) > 1)
      return getElement_Error; // input error
    return getElement_Operator;

  default:
    return getElement_Error; // input error
  }
}

int charType(char ch) {
  if (isdigit(ch))
    return charType_Digit;
  else if (ch == '.')
    return charType_Dot;
  else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' ||
           ch == '(' || ch == ')')
    return charType_Operator;
  else
    return charType_Other;
}

int getPriority(char ch) {
  switch (ch) {
  case '(':
    return 0;
  case '^':
    return 3;
  case '*':
  case '/':
    return 2;
  case '+':
  case '-':
    return 1;
  default:
    return -1;
  }
}