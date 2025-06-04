/* Program suite to illustrate input of several numbers */
/*    this is program 4 */

#include <stdio.h>

int
main (void)
{
  double a, b;

  printf ("part 4:  reading two values, separated by the word noyce\n");

  printf ("      enter values: ");
  scanf ("%lfnoyce%lf", &a, &b);

  printf ("      values read:  %lf  %lf\n\n", a, b);

  /* interesting test cases:
          1.5-3.5
          1.5noyce2.5
          1.5 noyce2.5
          1.5noyce 2.5  */

  return 0;
} // main
