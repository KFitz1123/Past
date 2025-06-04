#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char** argv) {


  // Make sure the user provided an N parameter on the command line
  if (argc != 2) {
    fprintf(stderr, "Usage: %s N (N must be >= 1)\n", argv[0]);
    exit(1);
  }

  // Convert the N parameter to an integer
  int N = atoi(argv[1]);

  // Make sure N is >= 1
  if (N < 1) {
    fprintf(stderr, "Invalid N value %d\n", N);
    exit(1);
  }

char nextChar = '\0';
int i = 0; // because special initial case
char gram[N];


//fills the first N terms of the 'gram' array

while((nextChar = fgetc(stdin))!= EOF && i < N){// grab the next char
  // modulo next char into the "next" slot in gram
  gram[i] = nextChar;
  i++;
}//while

// prints first trigram if N< length of input string

if(nextChar != EOF || i == N){
 for(int j = 0; j < N; j++){
    printf("%c", gram[j]);
  }//for
  printf("\n");
}//if

//prints standard cases for Ngrams

while(nextChar != EOF){// grab the next char
  // modulo next char into the "next" slot in gram
  gram[i%N] = nextChar;
  i++;
  nextChar = fgetc(stdin);
  // print current Ngram
  for(int j = 0; j < N; j++){
    printf("%c", gram[(i + j)%N]);
    }//for
  printf("\n");
}//while

  return 0;
}
