/* Program suite to illustrate input of several numbers */
/*    this is program 1a */

#include <stdio.h>

int
main (void)
{
  double a, b;

  printf ("part 1:  reading two values, separated by white space\n");

  printf ("   approach 1:  use two scanf statements\n");

  printf ("      enter first value: ");
  scanf ("%lf", &a);

  printf ("      enter second value: ");
  scanf ("%lf", &b);
  printf ("      values read:  %lf  %lf\n\n", a, b);

  /* interesting test cases:
        1.5 and 2.5 on separate lines
        1.5 2.5 on the same line
        1.52.5 as two numbers squeezed together without intervening whitespace
  */
  return 0;
} // main
