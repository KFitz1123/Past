/* This program illustrates how to 
 *     connect to the Scribbler robot, 
 *     beep, and 
 *     disconnect. 
 */

#include <MyroC.h>          /* include the signatures for Scribbler commands */

int
main (void)
{
  rConnect ("/dev/rfcomm0"); /* connect to Scribbler */
  rBeep (1,550);             /* beep for 1 second at a frequency of 550 Hz. */
  rBeep (0.5, 600);
  rBeep (2, 700);
  rBeep (2.5, 15000);
  rDisconnect ();            /* disconnect from Scribbler */
  return 0;                  /* return, indicating no errors have occurred */
} /* main */
