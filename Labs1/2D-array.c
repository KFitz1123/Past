/* Program to demonstrate variable initialization and 
 * compiler-based size inferences 
 */
#include <stdio.h>

int
main (void)
{
  int i; // counter variable

  //question 7a
  //To be able to compile the program, the number of columns in the array must be specified (the number of rows can but doesn't need to be specified)
  
  int array1[][3] = {{4, 5, 3}, {5, 3, 5}, {5, 2, 8}};
  //question 7b
  //36 bytes for the whole array
  //row 1 = 12 bytes
  //row 2 = 12 bytes
  //row 3 = 12 bytes

  //question 7c
  // holds 9 elements
  
  int array2[][5] = {{3, 4, 1}, {6, 3, 2, 4, 1}, {3, 5}};
  //question 7b 
  //60 bytes for the whole array
  //row 1 = 20 bytes
  //row 2 = 20 bytes
  //row 3 = 20 bytes

  //question 7c
  // holds 15 elements
  
  int array3[2][2] = {{5, 3}, {2, 1}};
  //question 7b 
  //16 bytes for the whole array
  //row 1 = 8 bytes
  //row 2 = 8 bytes

    //question 7c
  // holds 4 elements

  
  // int array4[3][] = {{2, 4, 3}, {4, 4, 1}, {1, 2, 3}};
  // int array5[][] = {{3, 2, 1}, {4, 3, 2}, {2, 4, 6}};

  int array6[3][4] = {{0, 1, 2, 3}, {2, 4, 6, 8}, {3, 6, 9, 12}};


  printf("array1 size = %lu\n", sizeof(array1)); 
  for (i = 0; i < 3; i++)
    printf("\tsize of row %d:  %lu\n", i, sizeof(array1[i]));
  printf("\n");

  printf("array2 size = %lu\n", sizeof(array2)); 
  for (i = 0; i < 3; i++)
    printf("\tsize of row %d:  %lu\n", i, sizeof(array2[i]));
  printf("\n");

  printf("array3 size = %lu\n", sizeof(array3)); 
  for (i = 0; i < 3; i++)
    printf("\tsize of row %d:  %lu\n", i, sizeof(array3[i]));
  printf("\n");

   //prints a 3 by 3 table and lists all elements in array1
   printf("array1 \n");
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 3; i++) {
      printf("%5.2d", array1[j][i]);
    }
    printf("\n");
  }

   printf("\n"); //prints newline for formatting purposes

  //prints a 5  by 3 table and lists all elements in array2
      printf("array2 \n");
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 5; i++) {
      printf("%5.2d", array2[j][i]);
    }
    printf("\n");
  }

  printf("\n"); //prints newline for formatting purposes

  //prints a 2 by 2 table and lists all elements in array3
     printf("array3 \n");
  for (int j = 0; j < 2; j++) {
    for (int i = 0; i < 2; i++) {
      printf("%5.2d", array3[j][i]);
    }
    printf("\n");
  }

    printf("\n"); //prints newline for formatting purposes
  
  //prints a 4 by 3 table and lists all elements in array6
     printf("array6 \n");
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 4; i++) {
      printf("%5.2d", array6[j][i]);
    }
    printf("\n");
  }
  
} // main
