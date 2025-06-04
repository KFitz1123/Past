/* Program suite to illustrate input of several numbers */
/*    this is program 1b */

#include <stdio.h>

int
main (void)
{
  double a, b;

  printf ("part 1:  reading two values, separated by white space\n");

  printf ("   approach 2:  combine into one scanf statement\n");

  printf ("      enter values: ");
  scanf ("%lf%lf", &a, &b);

  printf ("      values read:  %lf  %lf\n\n", a, b);

  /* interesting test cases:
          1.5 2.5  on one line or on separate lines
          1.52.5
          1.5-2.5  */
  return 0;
} // main
