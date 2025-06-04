
#ifndef __LISTQUEUE_H__
#define __LISTQUEUE_H__
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STRLEN 50

typedef struct node {
  char * data;
  struct node * next;
} queueNode;

typedef struct {
  queueNode * head;
  queueNode * tail;
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
