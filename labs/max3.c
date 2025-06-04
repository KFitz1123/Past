#define MAXM(X,Y) ((X) > (Y) ? (X) : (Y))
#include <stdio.h>
int
maxf (int x, int y)
{
  return x > y ? x : y;
  } // maxf

int
main (void) {
  int i;
  int x = 0;
  /*
  for (i = 0; i < 100000000; i++)
    x = MAXM (x, i);
  */

   float f = MAXM (3.5f, 2.3f);
  printf ("The max is %f\n", f); 
  return 0;
} // main

