#define _GNU_SOURCE

#include <assert.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

int round_up(int x);
#define PAGE_SIZE 0x1000

int main(int argc, char** argv) {

  printf("mallocing 2048(x should == 1)\n");
  void* x = malloc(1028);
  printf("mallocing 2048 again\n");
  void* y = malloc(1028);
  printf("useable size mallocing on a brand new page : %zu \n",malloc_usable_size(x));
  printf("useable size mallocing on an added page : %zu \n",malloc_usable_size(y));
 for(int i = 0; i<8; i++) {
 printf("mallocing 512 again\n");
  x = malloc(500);
 }
  free(x);
  // //size_t test = 447;
  // int result = round_up(447);
  // //int result = ((test / PAGE_SIZE) + 1) * PAGE_SIZE;
  // //printf("%d", result);
  return 0;
}

int round_up(int x) {
  int y = 16;
  while (y < x) {
    y = y * 2;
  }
  return y;
}