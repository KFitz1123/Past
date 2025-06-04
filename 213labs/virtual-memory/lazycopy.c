#define _GNU_SOURCE
#include "lazycopy.h"

#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

/**
 * This function will be called at startup so you can set up a signal handler.
 */
void seg_handler(int signal, siginfo_t* info, void* ctx);

/**
 * Create a linked list struct to store
 */
 typedef struct list_node{
      void* ch_strt;
      void* ch_end;
      struct list_node* next;
  }list_node_t;

  typedef struct ch_list{
      list_node_t* first;
      int size;
  }ch_list_t;

ch_list_t* lst;


void chunk_startup() {

  struct sigaction seg;
  memset(&seg, 0, sizeof(struct sigaction));
  seg.sa_sigaction = seg_handler;
  seg.sa_flags = SA_SIGINFO;

  if(sigaction(SIGSEGV, &seg, NULL) != 0) {
    perror("sigaction failed");
    exit(2);
  }

  lst = malloc(sizeof(ch_list_t));
  lst->first = NULL;
  lst->size = 0;
}


/**
  * What do you do when there is a seg fault? = malloc(sizeof(ch_list_t))
  */
void seg_handler(int signal, siginfo_t* info, void* ctx) {
  intptr_t infoint = (intptr_t) info->si_addr;
  printf("info = %ld\n", infoint);
  printf("Woah - a seg fault\n");

  list_node_t* cur = lst->first;

  while (cur != NULL) {
    //printf("cur: %ld", (intptr_t) cur->ch_strt);
    if ((((intptr_t) cur->ch_strt) < infoint) && (((intptr_t) cur->ch_end) > infoint)) {
      //print statement for fun
      printf("strt: %ld\n end: %ld\n", (intptr_t) cur->ch_strt, (intptr_t) cur->ch_end);

       void* data = malloc(sizeof(void*) * CHUNKSIZE);    //NEW
        memcpy(data,cur->ch_strt, CHUNKSIZE);             //NEW
      
      
      cur->ch_strt = mmap(cur->ch_strt, CHUNKSIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED | MAP_FIXED, -1, 0);
      cur->ch_end = cur->ch_strt + CHUNKSIZE;

      memcpy(cur->ch_strt,data, CHUNKSIZE);               //NEW

      break;
    }
    cur = cur->next;
  }

  if(cur == NULL) {
    printf("This is a regular Seg Fault, do better\n");
    exit(EXIT_FAILURE);
  }

}


/**
 * This function should return a new chunk of memory for use.
 *
 * \returns a pointer to the beginning of a 64KB chunk of memory that can be read, written, and
 * copied
 */
void* chunk_alloc() {
  // Call mmap to request a new chunk of memory. See comments below for description of arguments.
  void* result = mmap(NULL, CHUNKSIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
  // Arguments:
  //   NULL: this is the address we'd like to map at. By passing null, we're asking the OS to
  //   decide. CHUNKSIZE: This is the size of the new mapping in bytes. PROT_READ | PROT_WRITE: This
  //   makes the new reading readable and writable MAP_ANONYMOUS | MAP_SHARED: This mapes a new
  //   mapping to cleared memory instead of a file,
  //                               which is another use for mmap. MAP_SHARED makes it possible for
  //                               us to create shared mappings to the same memory.
  //   -1: We're not connecting this memory to a file, so we pass -1 here.
  //   0: This doesn't matter. It would be the offset into a file, but we aren't using one.

  // Check for an error
  if (result == MAP_FAILED) {
    perror("mmap failed in chunk_alloc");
    exit(2);
  }

  // Everything is okay. Return the pointer.
  return result;
}

/**
 * Create a copy of a chunk by copying values eagerly.
 *
 * \param chunk This parameter points to the beginning of a chunk returned from chunk_alloc()
 * \returns a pointer to the beginning of a new chunk that holds a copy of the values from
 *   the original chunk.
 */
void* chunk_copy_eager(void* chunk) {
  // First, we'll allocate a new chunk to copy to
  void* new_chunk = chunk_alloc();

  // Now copy the data
  memcpy(new_chunk, chunk, CHUNKSIZE);

  // Return the new chunk
  return new_chunk;
}

/**
 * Create a copy of a chunk by copying values lazily.
 *
 * \param chunk This parameter points to the beginning of a chunk returned from chunk_alloc()
 * \returns a pointer to the beginning of a new chunk that holds a copy of the values from
 *   the original chunk.
 */
void* chunk_copy_lazy(void* chunk) {
  // Just to make sure your code works, this implementation currently calls the eager copy version
  void* new_chunk;

  new_chunk = mremap(chunk, 0, CHUNKSIZE, MREMAP_MAYMOVE);
  mprotect(chunk, CHUNKSIZE, PROT_READ);
  mprotect(new_chunk, CHUNKSIZE, PROT_READ);


  if(lst->first == NULL){
    lst->first = malloc(sizeof(list_node_t));
    lst->first->ch_strt = chunk;
    lst->first->ch_end = chunk + CHUNKSIZE;
    lst->first->next = NULL;
    lst->size++;
  }
  else{
    list_node_t* oldchunk = malloc(sizeof(list_node_t));
    oldchunk->next = lst->first;
    oldchunk->ch_strt = chunk;
    oldchunk->ch_end = chunk + CHUNKSIZE;
    lst->first = oldchunk;
    lst->size++;
  }

    list_node_t* newnode = malloc(sizeof(list_node_t));
    newnode->next = lst->first;
    newnode->ch_strt = new_chunk;
    newnode->ch_end = new_chunk + CHUNKSIZE;
    lst->first = newnode;
    lst->size++;

  return new_chunk;

  // Your implementation should do the following:
  // 1. Use mremap to create a duplicate mapping of the chunk passed in
  // 2. Mark both mappings as read-only
  // 3. Keep some record of both lazy copies so you can make them writable later.
  //    At a minimum, you'll need to know where the chunk begins and ends.

  // Later, if either copy is written to you will need to:
  // 1. Save the contents of the chunk elsewhere (a local array works well)
  // 2. Use mmap to make a writable mapping at the location of the chunk that was written
  // 3. Restore the contents of the chunk to the new writable mapping
}
