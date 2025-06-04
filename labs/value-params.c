/* value-params.c
 *
 * Demonstrates scoping of variable names and passing values into functions.
 */

#include <stdio.h>

int
procA (int a, int b)
{
  printf ("procA1  a=%d, b=%d\n", a, b);
  a = 5;
  b = 6;
  printf ("procA2  a=%d, b=%d\n", a, b);
  return a + b;
} // procA

void
procB (int x, int y)
{
  int z = procA (x, y);
  printf ("procB1  x=%d, y=%d, z=%d\n", x, y, z);
  x = 5;
  y = 6;
  printf ("procB2  x=%d, y=%d, z=%d\n", x, y, z);
} // procB

int
main (void)
{
  int x, y;
  x = 2;
  y = 3;
  printf ("main1   x=%d, y=%d\n", x, y);
  procB (y, x);
  printf ("main2   x=%d, y=%d\n", x, y);

  return 0;
} // main
