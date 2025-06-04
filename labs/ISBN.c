#include <stdio.h>

int
main(void)
{
  int num=0;
  int x=0; 
  int total=0;
  char input=0;

  for(x=1;x<10;x++)
  {scanf("%c",&input);
    num= input - '0';
    if (x==2 ||x==4)
      printf("-%d", num);
    else 
    printf("%d",num);
    total= total + (x * num);
    }
  

 
  
   num= total % 11;
  if (num<10)
  printf("-%d/n", num);
  else printf ("-x/n");
  return 0;
}
