/* program illustrating arrays, strings, and pointers */

#include <stdio.h>
#include <string.h>


int
main (void)
{
 char str[16] = "isawesome";
char isawesome[32] = "computerscience";



 int l = (strlen (str)) / 2);
     int i =0;
     for (i=0; i < l; i++) {
      char temp;
     temp = str[i];
             int a = (strlen (str) - i - 1);
             str[i] = a;
             str[a] = temp;
           
     }

     for (int i = 0; i < strlen(str); i++){
       
       printf ("%c", str[i]);}

 
     //printf("computer\vscience\b\b\b\b\bis\vawesome\n" );
 


 
  return 0;

             
}
