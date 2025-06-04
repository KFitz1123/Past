#include "sorted-list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Initialize a sorted list.
 *
 * \param lst This is a pointer to space that should be initialized as a sorted list. The caller of
 * this function retains ownership of the memory that lst points to (meaning the caller must free it
 * if the pointer was returned from malloc)
 */
void sorted_list_init(sorted_list_t* lst) {
  lst->length = 0;
  lst->first = NULL;
}

/**
 * Destroy a sorted list. Free any memory allocated to store the list, but not the list itself.
 *
 * \param lst This is a pointer to the space that holds the list being destroyred. This function
 * should free any memory used to represent the list, but the caller retains ownership of the lst
 * pointer itself.
 */
void sorted_list_destroy(sorted_list_t* lst) {
  while(lst->length != 0){
    node_t* temp  = lst->first->next;
    free(lst->first);
    lst->first = temp;
    lst->length--;
  }
}

/**
 * Add an element to a sorted list, maintaining the lowest-to-highest sorted order.
 *
 * \param lst   The list that is being inserted to
 * \param value The value being inserted
 */
int sorted_list_insert(sorted_list_t* lst, int value) {
  node_t* newnode = malloc(sizeof(node_t));
  newnode->value = value;
  if(lst->length == 0){
    lst->first = newnode;
    lst->length++;
    return 0;
  }
  else{
  node_t* current = lst->first;
  //edge case, value is less than first in list
    if(value < current->value){
      newnode->next = current;
      lst->first = newnode;
      }
      else{


      while(current->next != NULL){
        if(current->next->value > value){//PROBLEM AREA
          newnode->next = current->next;
          current->next = newnode;
          lst->length++;
          return 0;
          }//if
        else{ //move to next
        current = current->next;
        }//else
      }//while


      //if next is NULL, add to end of list
      newnode->next = current->next;
      current->next = newnode;
      lst->length++;
      }//else 2

  }//else 1
 return 0;
}

/**
 * Count how many times a value appears in a sorted list.
 *
 * \param lst The list being searched
 * \param value The value being counted
 * \returns the number of times value appears in lst
 */
size_t sorted_list_count(sorted_list_t* lst, int value) {
  if(lst->length ==0) return 0;

  node_t* current = lst->first;
  while(current != NULL){
    if(current->value == value){
      //count number and return
      size_t count = 0;
      while(current != NULL && current->value == value){
        current = current->next;
        count++;
      }//while
      return count;
    }//if
    else{ //move to next
    current = current->next;
    }//else
  }//while

  return 0;
}

/**
 * Print the values in a sorted list in ascending order, separated by spaces and followed by a
 * newline.
 *
 * \param lst The list to print
 */
void sorted_list_print(sorted_list_t* lst) {
 node_t* current = lst->first;
 while(current->next != NULL){
  printf("%d ",current->value );
  current = current->next;
 }
 printf("%d\n",current->value);
}


