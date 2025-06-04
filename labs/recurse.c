#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void printreverse(char* word){
  if(word + 1 == '\0')
     printf("%c", *word);
  else
    {
     
      printreverse(word + 1);
      printf("%c", *word);
}
}

int
main(void)
{
  char* word = NULL;
  printf("please give me a string fine sir: ");
  scanf("%s", word);
  printreverse(word);
  return 0;
 }

