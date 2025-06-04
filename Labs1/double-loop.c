/* Program to review a loop with doubles */

#include <stdio.h>

int
main()
{
  double inc = 1.0/10.0;
  double val = 1000.0;
  double end = 1001.0;
  double sum = 0.0;

  printf("loop with doubles from %22.15lf to %22.15lf by increment %22.15lf\n",
	 val, end, inc);

  while (val <= end)
    {
      sum += val;                                   /* add to sum and print */
      printf("val = %22.15lf;  sum = %22.15lf\n", val, sum);

      val += inc;         /* increment val for loop test and next iteration */
    }

  printf("loop terminated with val = %22.15lf;  sum = %22.15lf\n", val, sum);

}
