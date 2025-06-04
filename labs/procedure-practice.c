/***********************************************************************
     * Name(s)  Kevin Fitzgerald, Lydia Ye              *
     * Assignment name (Lab procedure-practice)                                  *
     *                                                                     *
     * Assignment for 1/30/2023                                           *
     ***********************************************************************/

    /* *********************************************************************
     * Academic honesty certification:                                     *
     *   Written/online sources used:                                      *
     *     CSC-161 reading-program development                             *
     *   Help obtained                                                     *
     *    Barbara Johnson                   *
     *          *
     *                                                                     *
     *   Signature:    Kevin Fitzgerald, Lydia Ye                                                    *
     ***********************************************************************/





#include <MyroC.h>
#include <stdio.h>
#include "scale-notes.h"

/* tune-forward plays six beeps in increasing pitch */
void
tune_forward (void)
{
  printf ("tune_forward \n") ;
  rBeep(1.0, pitchC5);
  rBeep(0.5, pitchDf5);
  rBeep(0.5, pitchCs5);
  rBeep(0.5, pitchD5);
  rBeep(0.5, pitchEf5);
  rBeep(0.5, pitchDs5);  
}// tune-forward

/* tune-backward plays six beeps in decreasing pitch */

void
tune_backward (void)
{
  printf ("tune_backward \n") ;
  rBeep(0.5, pitchDs5);
  rBeep(0.5, pitchEf5);
  rBeep(0.5, pitchD5);
  rBeep(0.5, pitchCs5);
  rBeep(0.5, pitchDf5);
  rBeep(1.0, pitchC5);
}//tune_backward

/* move_clockwise moves the robot forward and turns it right three times each */

void move_clockwise (void)
{
  printf ("Move_clockwise \n") ;
  rForward(1.0, 0.5);
  rTurnRight(1.0,1.0);
  rForward(1.0, 0.5);
  rForward(1.0, 0.5);
  rTurnRight(1.0,1.0);
  rTurnRight(1.0,1.0);
} //move_clockwise

/* move_counterclockwise moves the robot forward and turns it left three times each */

void move_counterclockwise (void)
{
  printf ("Move_counterclockwise \n") ;
  rForward(1.0, 0.5);
  rTurnLeft(1.0,1.0);
  rForward(1.0, 0.5);
  rForward(1.0, 0.5);
  rTurnLeft(1.0,1.0);
  rTurnLeft(1.0,1.0);
}//move_counterclockwise

/* main program entry */

int main (void)
{
  rConnect ("/dev/rfcomm0");

  /* tune-forward plays six beeps in increasing pitch */
  
  printf("Starting tune_forward\n");
  tune_forward ();

  /* move_clockwise moves the robot forward and turns it right three times each */

  printf("Starting move_clockwise\n");
  move_clockwise ();

  /* tune-backward plays six beeps in decreasing pitch */ 
  
  printf("Starting tune_backward\n");
  tune_backward ();

  /* move_counterclockwise moves the robot forward and turns it left three times each */
  
  printf("Starting move_counterclockwise\n");
  move_counterclockwise ();

  /* tune-forward plays six beeps in increasing pitch */
  
  printf("Starting tune_forward\n");
  tune_forward ();

  /* move_clockwise moves the robot forward and turns it right three times each */
  
  printf("Starting move_clockwise\n");
  move_clockwise ();

  // finish with no errors
  rDisconnect ();
  
  return 0;
}//main
