#include "arrayqueue.h"




int main(void){

  stringQueue *  ADT;
  initialize(ADT);
  enqueue(ADT, "A");
  printf("%s\n", front(ADT)); // A
  enqueue(ADT, "B");
  printf("%s\n",front(ADT)); // A
  dequeue(ADT);
          printf("%s\n",front(ADT)); // B




  return 0;
}
