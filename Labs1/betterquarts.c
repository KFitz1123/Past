//
//
//

#include <stdio.h>

int main(void)
{
  float gallons=3, quarts=2, pints=1,totalQuarts,liters;
  totalQuarts= 4 * gallons + quarts + (pints / 2);
  liters = totalQuarts * 0.95;
  printf("Total liters =  %f \n", liters);
  return 0;
}
  
