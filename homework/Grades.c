  /***********************************************************************
     * Name: Kevin Fitzgerald                                                                                   *
     * Assignment name: Homework  1                                                                     *
     *                                                                                                                             *
     * Assignment for  2/17/23                                                                                     *
     ***********************************************************************/

    /* *********************************************************************
     * Academic honesty certification:                                     *
     *   My signature below confirms that the above list of sources        *
     *   is complete AND that I/we have not talked to anyone else          *
     *   (e.g., CSC 161 students) about the solution to this problem       *
     *                  
     *  none other than class readings                   
     *            *
     *   Signature:             Kevin Fitzgerald                                           *
     ***********************************************************************/

#include <stdio.h>

int 
main (void)
{
int grade=0;

printf("please input your grade to the nearest whole number (between 0 and 100)\n");
scanf("%d",&grade);
if (grade<0)
  grade=0;
if (grade>100)
  grade=100;
int letter=grade/10;
int plus=grade%10;
printf("Your Grade is: ");
if(letter<6)
	printf("F\n"); // if grade is below 60% it is an F
else if (letter == 10)
	printf("A+\n"); // if grade is 100%, it is an A+
else {switch (letter)
{
 case 6: printf("D");
    break;
 case 7:printf("C");
    break;
 case 8:printf("B");
    break;
 case 9:printf("A");
    break;
  default:
    printf("please input valid score");
    break;
}
if (0<=letter && letter<=2)
  printf("-\n"); //if second digit is from 0 to 2, add a -
else if(letter>=8)
  printf("+\n"); //if second digit is either 8 or 9, add a +
else printf("\n");
}
return 0;
}
/*==========================================
Test Plan for Grade Translation program
==========================================

The test plan will involve testing valid and expected inputs to determine that the program
chooses the correct letter grade and modifier for a selection of values.  It will also
include testing the edge cases for the interval 0 <= n <= 100 and testing values 
beyond the interval.

This test will NOT include possible user errors involving completely invalid inputs such
as non-numeric input nor floating point (i.e. real) numbers since we have not yet
learned how to recover from those.

****** Testing valid inputs **********
input: 89
expected output: B+

input: 72
expected output: C-

input: 95
expected output: A

This tests three of five letter grades and all of the modifiers


****** Testing edge cases *************
input: 0
expected output: F

input: 100
expected output: A+

****** Testing invalid input *************
input: -1
expected output: F

input: 101
expected output: A+ 

====================================
Test Script
====================================
Script started on Thu Sep 26 14:47:03 2019


Script started on 2023-02-16 20:30:08-06:00 [TERM="xterm-256color" TTY="/dev/pts/0" COLUMNS="80" LINES="15"]
[?2004hfitzgera@holberton:homework$ ./grade
[?2004lbash: ./grade: No such file or directory
[?2004hfitzgera@holberton:homework$ clang -o  [Kgrades Grades.c

***Testing expected inputs***

[?2004l[?2004hfitzgera@holberton:homework$ ./grades
[?2004lplease input your grade to the nearest whole number (between 0 and 100)
89
Your Grade is: B+
[?2004hfitzgera@holberton:homework$ ./grades
[?2004lplease input your grade to the nearest whole number (between 0 and 100)
72
Your Grade is: C
[?2004hfitzgera@holberton:homework$ ./grades
[?2004lplease input your grade to the nearest whole number (between 0 and 100)
95
Your Grade is: A+

***Testing Edge/extreme Cases***

[?2004hfitzgera@holberton:homework$ ./grades
[?2004lplease input your grade to the nearest whole number (between 0 and 100)
0
Your Grade is: F
[?2004hfitzgera@holberton:homework$ ./grades100[K[K[K
[?2004lplease input your grade to the nearest whole number (between 0 and 100)
100
Your Grade is: A+
[?2004hfitzgera@holberton:homework$ ./grades
[?2004lplease input your grade to the nearest whole number (between 0 and 100)
-1
Your Grade is: F
[?2004hfitzgera@holberton:homework$ ./grades
[?2004lplease input your grade to the nearest whole number (between 0 and 100)
101
Your Grade is: A+
[?2004hfitzgera@holberton:homework$ exir[Kt
[?2004lexit

Script done on 2023-02-16 20:32:26-06:00 [COMMAND_EXIT_CODE="0"]


==========================================
Conclusion
=========================================

The program works as expected on valid input, including edge cases.  It also handles
expected user input errors when the input is out of range.  

With the exception that it cannot yet handle non-integer input, the program is working*/
