#ifndef __ARRAYQUEUE_H__
#define __ARRAYQUEUE_H__
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_QUEUE_SIZE 50
/* size of all queue arrays */

typedef struct {
  int first;
  int last;
  int count;
  char * queueArray[MAX_QUEUE_SIZE];
} stringQueue;



void
initialize (stringQueue * queue);

bool
isEmpty (const stringQueue * queue);

bool
isFull (const stringQueue * queue);

bool
enqueue (stringQueue * queue, char * item);
/* returns whether item was successfully enqueued */

char *
dequeue (stringQueue * queue);
/* returns string removed from queue */

char *
front (const stringQueue* queue);
#endif
