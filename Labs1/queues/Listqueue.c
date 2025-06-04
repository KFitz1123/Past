#include "Listqueue.h"




void
initialize (stringQueue * queue)
{
  queue->head = NULL;
  queue->tail = NULL;
 
}
bool
isEmpty (const stringQueue * queue)
{
  if ((queue->head == NULL) && (queue->tail == NULL)){
    return true;
  }
  else{
    return false;
  }
}

bool
isFull (const stringQueue * queue)
{
char * temp = malloc(sizeof(char)*MAX_STRLEN);
if(temp==NULL)
  {
    free(temp);
    return true;
  }
  else{
    free(temp);
    return false;
  }
}

bool
enqueue (stringQueue * queue, char * item)
/* returns whether item was successfully enqueued */
{
  if(isFull(queue))
    {
      return false;
    }
  else
    if(isEmpty(queue))
      {
        queueNode * newNode = malloc(sizeof(queueNode));
        newNode->next= NULL;
        newNode->data = malloc(sizeof(char)*strlen(item + 1));
        strcpy(newNode->data, item);
        queue->head = newNode;
        queue->tail = newNode;
        return true;
      }
    else {
      queueNode * newNode = malloc(sizeof(queueNode));
      newNode->next= NULL;
      newNode->data = malloc(sizeof(char)*strlen(item + 1));
      strcpy(newNode->data, item);
      queue->tail->next = newNode;
      queue->tail = newNode;
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
   
    char * tempstring = malloc(sizeof(char)*strlen(queue->head->data));
    strcpy(tempstring, queue->head->data);
    
    queueNode * tempnode = queue->head;
    queue->head = queue->head->next;
    free(tempnode->data);
    free(tempnode);

    
    return tempstring;
  }
}
char *
front (const stringQueue* queue)
{
  return queue->head->data;
}
