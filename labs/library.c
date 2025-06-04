#include "header.h"
#ifndef __HEADER_H__
#define __HEADER_H__
#endif
#define TEST(EXP,RESULT) if (EXP != RESULT) { ++errors; printf ("Did not get expected result for %s.\n", #EXP); }

int 
fun (int x)
{
  return x;
  // wasn't that fun?
} // fun

