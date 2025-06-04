  /***********************************************************************
     * Name: Kevin Fitzgerald                                                                                   *
     * Assignment name: Homework  1 pt.2                                                                     *
     *                                                                                                                             *
     * Assignment for  2/17/23                                                                                     *
     ***********************************************************************/

    /* *********************************************************************
     * Academic honesty certification:                                     *
     *   My signature below confirms that the above list of sources        *
     *   is complete AND that I/we have not talked to anyone else          *
     *   (e.g., CSC 161 students) about the solution to this problem       *
     *                  
     *  none                    
     *            *
     *   Signature:             Kevin Fitzgerald                                           *
     ***********************************************************************/

#include <stdio.h>

/*
Pre: two numbers which cannot both be 0
Post: returns an Int
*/
int 
euclids(int1,int2)
{
    int Rem = 0;
   
    while (int2>0||int2<0)
      {Rem=int1%int2;
int1=int2;
 int2=Rem;}
return int1;
}
int 


main (void)
{
  int GCD=0;
    int int1=0;
    int int2=0;
printf("input two variables, and this will return the greatest common denominator:\n");
 scanf("%d %d",&int1, &int2);
 if (int1==0||int2==0)//if either  int is 0, return 0
     printf("Your Greatest Common Denomenator is: 0\n");
 else 
   {GCD = euclids(int1,int2);
     printf("Your Greatest Common Denomenator is: %d \n",GCD);
       }
return 0;
}
/*==========================================
Test Plan for Greatest Common Denomentor program
==========================================

The test plan will involve testing valid and expected inputs to determine that the program
chooses the correct GCD for a selection of values.  It will also
include testing the edge cases for int1=0 and int2=0

This test will NOT include possible user errors involving completely invalid inputs such
as non-numeric input nor floating point (i.e. real) numbers since we have not yet
learned how to recover from those.

****** Testing valid inputs **********
input: 20, 40
expected output: 20

input: 13, 27
expected output: 1

input: 4, 2
expected output: 2

This tests for all types of situations, including primes


****** Testing edge cases *************
input: 0, 0
expected output: 0

input: 0 20
expected output: 0

====================================
Test Script
====================================
Script started on 2023-02-16 21:02:55-06:00 [TERM="xterm-256color" TTY="/dev/pts/0" COLUMNS="80" LINES="37"]
[?2004hfitzgera@holberton:homework$ exit./grades[4Pexit[K./gcd


[?2004linput two variables, and this will return the greatest common denominator:
20 40
Your Greatest Common Denomenator is: 20 
[?2004hfitzgera@holberton:homework$ ./gcd
[?2004linput two variables, and this will return the greatest common denominator:
13 27
Your Greatest Common Denomenator is: 1 
[?2004hfitzgera@holberton:homework$ 4 2
[?2004lbash: 4: command not found
[?2004hfitzgera@holberton:homework$ 4 2./gcd
[?2004linput two variables, and this will return the greatest common denominator:
4 2
Your Greatest Common Denomenator is: 2 
[?2004hfitzgera@holberton:homework$ ./gcd[2P4 2./gcd
[?2004linput two variables, and this will return the greatest common denominator:
0 0
*** edge cases***
Your Greatest Common Denomenator is: 0
[?2004hfitzgera@holberton:homework$ ./gcd
[?2004linput two variables, and this will return the greatest common denominator:
0 20
Your Greatest Common Denomenator is: 0
[?2004hfitzgera@holberton:homework$ exit
[?2004lexit

Script done on 2023-02-16 21:04:18-06:00 [COMMAND_EXIT_CODE="0"]



==========================================
Conclusion
=========================================

The program works as expected on valid input, including edge cases. 

With the exception that it cannot yet handle non-integer input, the program is working*/
