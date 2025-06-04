    /***********************************************************************
     * Name(s): Kevin, Shayak                                              *
     * Assignment name (Project  2)                                        *
     *                                                                     *
     * Assignment for 7th March, 2023                                      *
     ***********************************************************************/

    /* *********************************************************************
     * Academic honesty certification:                                     *
     *   Written/online sources used:                                      *
     *    CSC 161 Readings                                                 *
     *   Help obtained: None                                               *
     *                                                                     *
     *   My/our signature(s) below confirms that the above list of sources *
     *   is complete AND that I/we have not talked to anyone else          *
     *   (e.g., CSC 161 students) about the solution to this problem       *
     *                                                                     *
     *   Signature: Kevin, Shayak                                          *
     ***********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* preconditions: Keyboard Input of an integer value between 1 and 100 (inclusive)
   postconditions: Program determines whether user's guess is higher, lower, correct, or invalid.
*/

int
main(void)
{
  srand(time(0)); 
  int limit = 100;
  int guess = 0;
  int i = 0;
  int ran = (rand() % limit) + 1; //Initialises a random number between 1 and 100 (inclusive)
  
  printf("Enter your first guess between 1 and 100 (inclusive)\n");
  
  while ( i <= 10 &&  guess != ran) { //While number of guesses is less than 10 and user has not inputted a correct guess, continue the loop
    scanf("%d",&guess); // Take input for guess variable from user
    if (guess >= 1 && guess <= 100){ //Checks the input range and handles input error
        if (guess < ran){
          printf("Incorrect, Guess Higher!\n");
        } else if (guess > ran) {
          printf("Incorrect, Guess Lower!\n");
        }} else {
        printf("Invalid Input, Please Enter Again!\n");
      }
     i++;
   }

   if (guess == ran){
          printf("Congrats, You Guessed the Number Correctly!\n");
   } else {
          printf("You are Out of Guesses! The number was %d\n", ran);
   }

  return 0;
} //main
