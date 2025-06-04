#include <stdio.h>
#define maxf(X,Y) ((X) > (Y) ? (X) : (Y))

/*int
maxf (int x, int y)
{
  return x > y ? x : y;
  } // maxf*/


/* Tests for a three-way maximum.
 * Precondition: pNumErrors has valid address for an integer
 * Postcondition: Increments the integer pointed to by pNumErrors if the
 * largest of a, b, and c is not equal to expected.
 */
void
check3 (int a, int b, int c, int expected, int * pNumErrors)
{
  int result = maxf (maxf (a, b), c);
  if (result != expected)
    {
      printf ("For max (max (%d, %d), %d), expected %d, got %d.\n",
              a, b, c, expected, result);
      (*pNumErrors)++;
    }
} // max3

int
main (void)
{
  int numErrors = 0;
  // Check various permutations
  check3 (1, 2, 3, 3, &numErrors);
  check3 (1, 3, 2, 3, &numErrors);
  check3 (2, 1, 3, 3, &numErrors);
  check3 (2, 3, 1, 3, &numErrors);
  check3 (3, 1, 2, 3, &numErrors);
  check3 (3, 2, 1, 3, &numErrors);

  return numErrors;
} // main
