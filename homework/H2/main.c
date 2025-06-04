#include "func.h"
   /***********************************************************************
     * Name: Kevin Fitzgerald                                              *
     * Homework 2                                                          *
     *                                                                     *
     * Assignment for 5/12/2023                                            *
     ***********************************************************************/

    /* *********************************************************************
     * Academic honesty certification:                                     *
     *   CSC 161 readings (Charater I/O, File input and Output, Command 
     * line agruments)                                                     *
     *                                                                     *
     *   Signature:  Kevin Fitzgerald                                      *
     ***********************************************************************/


int
main(int argc, char * argv[])
{
  printf("this program tells you some statistical information about the data ontained in the input file\n File must be integers with a new line between each datapoint\n");
  if (argc != 2)
    {
      printf("Please include one input file  when running. Try again\n");
      return 0;
    }// makes sure that the commandline input is valid
  
  FILE* datafile = fopen (argv[1], "r");// open file
  
  
  if(datafile == NULL)
    {
      printf("File could not be opened. Please try again\n");
      return 0;
    }// makes sure that the file can be opened
   
 
  struct data * stored = store(datafile); // stores file data in an array
       
 

  Datanalysis(stored);      //analyzes array and prints a table
  
  if (fclose (datafile))              //closes file                       
  {
    fprintf (stderr, "%s: Error closing file %s: %s\n",
             argv[0], argv[1], strerror(errno));
    return EXIT_FAILURE;
  }
 
  free(stored);      //frees node for data
  printf("task successful. Have a nice day\n");
  return 0;
}
