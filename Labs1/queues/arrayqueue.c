#include "arrayqueue.h"




void
initialize (stringQueue * queue)
{
  queue->first = 0;
  queue->last = MAX_QUEUE_SIZE - 1;
  queue->count = 0;
}
bool
isEmpty (const stringQueue * queue)
{
  if (queue->count == 0){
    return true;
  }
  else{
    return false;
  }
}

bool
isFull (const stringQueue * queue)
{ if (queue->count == MAX_QUEUE_SIZE){
    return true;
  }
  else{
    return false;
  }
}

bool
enqueue (stringQueue * queue, char * item)
/* returns whether item was successfully enqueued */
{
  if(isFull(queue))
    {return false;
    }
  else{
    char * tempstring = malloc(sizeof(char)*strlen(item));
    strcpy(tempstring, item);
    
    queue->last = (queue->last + 1) % MAX_QUEUE_SIZE;
    queue->queueArray[queue->last] = tempstring;
    queue->count++;
    
  
    return true;
  }
}

char *
dequeue (stringQueue * queue)
/* returns string removed from queue */
{
  if(isEmpty(queue))
    {return NULL;
    }
  else{
    int current = queue->first;
    char * tempstring = malloc(sizeof(char)*strlen(queue->queueArray[current]));
    strcpy(tempstring, queue->queueArray[current]);
    queue->count--;
    queue->first = (queue->first + 1) % MAX_QUEUE_SIZE;
    free(queue->queueArray[current]);
    return tempstring;
  }
}
char *
front (const stringQueue* queue)
{
  return queue->queueArray[queue->first];
}
