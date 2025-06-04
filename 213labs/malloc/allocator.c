#define _GNU_SOURCE

#include <assert.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

/* Questions to ask fro Wednesday class:
  - issue with wasting a full object?

*/

// The minimum size returned by malloc
#define MIN_MALLOC_SIZE 16
// Our Magic number
#define MAGIC 457

// proper round up
size_t round_up(size_t x);

// The size of a single page of memory, in bytes
#define PAGE_SIZE 0x1000

typedef struct __attribute__((packed)) header {
  int size;
  int magic;
} header_t;

// nodes for the free list
typedef struct free_node {
  struct free_node* next;
} free_node_t;

// Global linked list
typedef struct free_list {
  header_t* head;
  free_node_t* first;
} free_list_t;

// make an array that stores all our free lists
free_list_t list_array[8] = {{NULL, NULL}};

// A utility logging function that definitely does not call malloc or free
void log_message(char* message);

//char buffer[128];

/**
 * Allocate space on the heap.
 * \param size  The minimium number of bytes that must be allocated
 * \returns     A pointer to the beginning of the allocated space.
 *              This function may return NULL when an error occurs.
 */
void* xxmalloc(size_t size) {
  // The entire implementation of this function should be replaced.
  // This is a basic starting point so you can start with a working allocator, but this
  // implementation wastes an enormous amount of space.
  // Round the size up to the next multiple of the page size
  void* chunk = NULL;
  size = round_up(size);

  if(size <= 0){
    log_message("zero was passed to xxmalloc\n");
    return chunk;
    }

  free_list_t list = {NULL, NULL};

  //set list to list held in array
  int list_array_loc;
  switch (size) {
    case 16:
      list = list_array[0];
      list_array_loc = 0;
      break;
    case 32:
      list = list_array[1];
      list_array_loc = 1;
      break;
    case 64:
      list = list_array[2];
      list_array_loc = 2;
      break;
    case 128:
      list = list_array[3];
      list_array_loc = 3;
      break;
    case 256:
      list = list_array[4];
      list_array_loc = 4;
      break;
    case 512:
      list = list_array[5];
      list_array_loc = 5;
      
      break;
    case 1024:
      list = list_array[6];
      list_array_loc = 6;
      break;
    case 2048:
      list = list_array[7];
      list_array_loc = 7;
      break;
    default:

      chunk = mmap(NULL, ((size / PAGE_SIZE) + 1) * PAGE_SIZE, PROT_READ | PROT_WRITE,
                   MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
      if (chunk == MAP_FAILED) {
        log_message("mmap failed! Giving up.\n");
        exit(2);
      }
      // returns the pointer to the large object
      return chunk;
      exit(EXIT_SUCCESS);
    }
  

  // either the list is empty, or we're out of chunks
  if (list.first == NULL) {
    //log_message("x");
    // maps  a new page
    void* new = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (new == MAP_FAILED) {
      log_message("mmap failed! Giving up.\n");
      exit(2);
    }  // error check

      //creates header and sets list.first to 'size' after the start of the header 
      list.head = new;
      list.head->size = (int)size;
      list.head->magic = MAGIC;
      list.first = (free_node_t*) (((intptr_t)new) + size);
      
    
    // points current to the start of the free list
    free_node_t* current = list.first;
    current->next = NULL;

    //loop starts after the header chunk plus the current which was initialized
    int i = 1;
    while (((i * size) + size) < PAGE_SIZE) {
      free_node_t* newnode = (free_node_t*)(((intptr_t)current) + size);  // PROBLEM AREA
      newnode->next = NULL;
      current->next = newnode;
      current = newnode;
      i++;
    }  // add nodes
    current = list.first;
    while(current != NULL){
      current = current->next;
    }
  }    // If list is empty

  chunk = list.first;
  list.first = list.first->next;
  list_array[list_array_loc] = list;
  
  return chunk;

  // TODO: malloc(32) moved to a new page, but wasted a full object.
}

/**
 * Get the available size of an allocated object. This function should return the amount of space
 * that was actually allocated by malloc, not the amount that was requested.
 * \param ptr   A pointer somewhere inside the allocated object
 * \returns     The number of bytes available for use in this object
 */
size_t xxmalloc_usable_size(void* ptr) {
  // If ptr is NULL always return zero
  if (ptr == NULL) {
    return 0;
  }

  // Treat the freed pointer as an integer
  intptr_t free_address = (intptr_t)ptr;

  // Round down to the beginning of a page
  intptr_t page_start = free_address - (free_address % PAGE_SIZE);
  
  // Cast the page start address to a header struct
  header_t* header = (header_t*) page_start;
  
  // Find the size of all chunks in this list
  size_t list_size = (size_t)header->size;
  if(header->magic == MAGIC){
    return list_size;
  } else {
    return 0;
  } // if
}


/**
 * Free space occupied by a heap object.
 * \param ptr   A pointer somewhere inside the object that is being freed
 */
void xxfree(void* ptr) {
  
  // Don't free NULL!
  if (ptr == NULL) return;

  // get the size of the object being freed
  size_t size_of_obj = xxmalloc_usable_size(ptr);
  free_list_t list;
  int list_array_loc;

  switch (size_of_obj) {
    case 16:
      list = list_array[0];
      list_array_loc = 0;
      break;
    case 32:
      list = list_array[1];
      list_array_loc = 1;
      break;
    case 64:
      list = list_array[2];
      list_array_loc = 2;
      break;
    case 128:
      list = list_array[3];
      list_array_loc = 3;
      break;
    case 256:
      list = list_array[4];
      list_array_loc = 4;
      break;
    case 512:
      list = list_array[5];
      list_array_loc = 5;
      break;
    case 1024:
      list = list_array[6];
      list_array_loc = 6;
      break;
    case 2048:
      list = list_array[7];
      list_array_loc = 7;
      break;
    default:
      return;
  } // switch

  // find location of object in the list
  intptr_t temp = (intptr_t) ptr;
  intptr_t loc = temp - (temp % size_of_obj);
  free_node_t* loc_node = (free_node_t*)loc;
  loc_node->next = list.first;
  list.first = loc_node;
  list_array[list_array_loc] = list;

  return;
}



/**
 * Print a message directly to standard error without invoking malloc or free.
 * \param message   A null-terminated string that contains the message to be printed
 */
void log_message(char* message) {
  // Get the message length
  size_t len = 0;
  while (message[len] != '\0') {
    len++;
  }

  // Write the message
  if (write(STDERR_FILENO, message, len) != len) {
    // Write failed. Try to write an error message, then exit
    char fail_msg[] = "logging failed\n";
    write(STDERR_FILENO, fail_msg, sizeof(fail_msg));
    exit(2);
  }
}

size_t round_up(size_t x) {
  size_t y = 16;
  while (y < x) {
    y = y * 2;
  }
  return y;
}