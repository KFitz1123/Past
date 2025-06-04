#ifndef SIZE
#define SIZE 5
#endif
#include <stdio.h>
int
main (void)
{
  int numEvens = 0;
  int i;
  int a[SIZE];

  a[0] = 0;
  for ( i = 0 ; i < SIZE ; i++ ) {
    a[i] = i + 2*a[i-1];
      if (a[i] % 2 == 0)
    numEvens++;
      #ifdef TESTING
       printf ("i = %d, a[i] = %d, numEvens= %d.\n", i, a[i], numEvens);
       #endif // TESTING
  }
    for (i = 0; i < SIZE; i++)
    printf ("a[%d] = %d\n", i, a[i]);

    printf ("Number of even numbers: %d\n", numEvens);
    
int
maxf (int x, int y)
{
  return x > y ? x : y;
} // maxf

        
  return 0;
} // main
