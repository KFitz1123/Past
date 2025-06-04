#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

// Implement your signal handling code here!
void seg_handler(int signal, siginfo_t* info, void* ctx);

__attribute__((constructor)) void init() {
  printf("This code runs at program startup\n");
  struct sigaction seg;
  memset(&seg, 0, sizeof(struct sigaction));
  seg.sa_sigaction = seg_handler;
  seg.sa_flags = SA_SIGINFO;

  if(sigaction(SIGSEGV, &seg, NULL) != 0) {
    perror("sigaction failed");
    exit(2);
  }

}
void seg_handler(int signal, siginfo_t* info, void* ctx) {
  // Print a message and set another alarm for one second
  srand(time(NULL));
  int r = rand()%8;
  switch(r){
    case 0: printf("You Can Do Better(probably)\n");
      break;
    case 1: printf("Better Luck Next Time\n");
      break;
    case 2: printf("At Least This Error Was Obvious\n");
      break;
    case 3: printf("Its A Good Thing You Cant Edit That Memory\n");
      break;
    case 4: printf("Have Fun Debugging\n");
      break;
    case 5: printf("Think of This as a Learning Opportunity\n");
      break;
    case 6: printf("It's not your Seg Fault! (It Is Though)\n");
      break;
    case 7: printf("Don't Give Up\n");
      break;

  }
  exit(EXIT_FAILURE);
}