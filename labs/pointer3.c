/* Program 3: Practice using procedures and parameters in C */

#include <stdio.h>

/* Example procedure demonstrating passing pointers */
void
pointersFunctionThreeInner (int * pr, int * ps) 
{  
  printf ("pointersFunctionThreeInner before :  pr = %p; *ps = %d\n", pr, *ps);
  
  *pr = 5;
  *ps = 6;
  
  printf ("pointersFunctionThreeInner after  :  pr = %p; *ps = %d\n", pr, *ps);
} // pointersFunctionThreeInner



/* Example procedure demonstrating passing values and pointers */
void
pointersFunctionThreeOuter (int a, int * pb) 
{  
  printf ("pointersFunctionThreeOuter before :  a = %d; *pb = %d\n", a, *pb);
  
  pointersFunctionThreeInner (&a, pb);

  printf ("pointersFunctionThreeOuter after  :  a = %d; *pb = %d\n", a, *pb);
} // pointersFunctionThreeOuter


/* main procedure to call other function and demonstrate values 
   before and after 
*/
int
main (void) 
{
  int x = 3;
  int y = 4;
  
  printf ("practice program 3\n");
  printf ("main before :  x = %d; y = %d\n", x, y);

  pointersFunctionThreeOuter (x, &y);

  printf ("main after  :  x = %d; y = %d\n", x, y);
  return 0;
} // main
