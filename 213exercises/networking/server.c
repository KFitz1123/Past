#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>

#include "message.h"
#include "socket.h"

void* worker(void*);

int main() {
    while (1) { 
  // Open a server socket
  unsigned short port = 0;
  int server_socket_fd = server_socket_open(&port);
 
  if (server_socket_fd == -1) {
    perror("Server socket was not opened");
    exit(EXIT_FAILURE);
  }
  // Start listening for connections, with a maximum of one queued connection
    if (listen(server_socket_fd, 1)) {
      perror("listen failed");
      exit(EXIT_FAILURE);
    }
    printf("Server listening on port %u\n", port);
    
    
       // Wait for a client to connect
    int client_socket_fd = server_socket_accept(server_socket_fd);
    if (client_socket_fd == -1) {
      perror("accept failed");
      exit(EXIT_FAILURE);
    }
     int* unique_socket = malloc(sizeof(int));
  unique_socket = &client_socket_fd;

pthread_t temp;
    if(pthread_create(&temp, NULL, worker, (void*)unique_socket)){
      perror("pthread create failed");
      exit(EXIT_FAILURE);
    }
    close(server_socket_fd);

}
  return 0; 
}

void* worker(void* descriptor){
  int client_socket_fd = *((int*) descriptor);
while (1) {  

  
 
    printf("Client connected!\n");

    // Send a message to the client
    int rc = send_message(client_socket_fd, "Hello client!");
    if (rc == -1) {
      perror("Failed to send message to client");
      exit(EXIT_FAILURE);
    }

  char* message;

  while(1){
    // Read a message from the client
    message = receive_message(client_socket_fd);
    if (message == NULL) {
      perror("Failed to read message from client");
      exit(EXIT_FAILURE);
    }

    // Print the message
    printf("Client sent: %s", message);

    // char* temp = message; 
    // while(*temp != '\0') {
    //   *temp = toupper(*temp); 
    //   temp++; 
    // }

    int rc = send_message(client_socket_fd, message);
    if (rc == -1) {
      perror("Failed to send message to server");
      exit(EXIT_FAILURE);
    }
    if(strcmp(message, "quit\n") == 0){
      // Free the message string
      printf("ending\n");
    free(message);
    // Close sockets
    close(client_socket_fd);
      break; 
    }
    }
  }

  return descriptor;
}
