#ifndef GETEXPRESSION_H

#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GETEXPRESSION_H

void releaseBuffer();

// The function get expression and store it in destination separately
// return 0 when enter quit, q etc.;
// return -1 when the input error;
// return 1 when the function run successfully
int getExpression(List *destination);

#endif