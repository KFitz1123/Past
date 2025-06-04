/*
	scanf-example.c
	
	Program to show simple use of scanf and the value it returns
	
	Author: April O'Neill
	Created: July 25, 2011
	
	Revised: 16 October 2012 by Henry M. Walker
	Revised October 10, 2022 by Barbara Z. Johnson
	
	*/

#include <stdio.h>

#define MAXSTR 30



void
funct1(void)
{
  char a[15];
  char b[15];
  printf("Please input your name, (first-name last-name)\n");
  scanf("%s%s",a,b);
  printf("Hello %s %s\n", a,b);
}

int
main (void)
{
  int numTokens = 0;
  double number = 0;
  char input[MAXSTR+1];     


  funct1();
    
  printf ("Enter a number of the double type: ");
  numTokens = scanf ("%lf", &number);

  if (numTokens > 0)
    printf ("\tYou entered the number \"%lf\".\n", number);
  else
    printf ("\tYou did not enter a number.\n");
  

  printf ("Enter a word no more than 30 characters long: ");
  numTokens = scanf("%s", input);

  if (numTokens > 0)
    printf ("\tYou entered the word \"%s\".\n", input);
  else
    printf ("\tYou did not enter a word.\n");    

  printf ("\n\tSummary\n");
  printf ("\tnumber:  %lf\n", number);
  
  if (numTokens > 0)
       printf ("\tstring:  %s\n", input);

  return 0;
} // main
