/*      tricky-ifs.c

	Original written by Henry Walker
	Revised: Barbara Z Johnson

*/

#include <stdio.h>


int main() {

int TEST = 1;

if (TEST)
   printf ("statement 1\n");
   printf ("statement 2\n");

if (TEST)
   {
      printf ("statement 3\n");
      printf ("statement 4\n");
   }

if (TEST)
   printf ("statement 5\n");
else
   printf ("statement 6\n");
   printf ("statement 7\n");

if (TEST)
   printf ("statement 8\n");
else
   {
      printf ("statement 9\n");
      printf ("statement 10\n");
   }

if (TEST == 1)
   printf ("statement 11\n");
else
   printf ("statement 12\n");

if (TEST = 1)
   printf ("statement 13\n");
else
   printf ("statement 14\n");

return 0;

}