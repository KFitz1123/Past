/* windchill.c
 *
 * Author: Barbara Z. Johnson and (your names here)
 * Date: June 20, 2022
 * Revised: (today's date)
 * Purpose: to calculate the windchill based on two inputs:
 *		temperature (Fahrenheit) assumed to be an integer
 *      windspeed (miles per hour) assumed to be an integer
 *		forumula:  Twc = F - (W * 0.7)
 *      forumula from  Tom Skilling at the Chicago Tribune
 */



/* program to classify integers into simple categories  */  

#include <stdio.h>  

int main () {    
	/* getting started by reading a number*/   

	printf ("program to classify integers\n");      
	int number;   
	printf ("Enter your integer candidate: ");   
	scanf ("%d", &number); 
   
	/* classify number */   
	if (number < 0)     
		printf ("%d is negative\n", number);   
	else if (number == 0)     
		printf ("number is zero\n");   
	else if  (number < 10)    
		printf ("%d is a single digit\n", number);   
	else if  (number <= 20)     
		printf ("%d has medium size\n", number);   
	else    
		printf ("%d is large\n", number);   
   
	return 0; 
}  
