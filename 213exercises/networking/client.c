#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "message.h"
#include "socket.h"

int main(int argc, char** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <server name> <port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // Read command line arguments
  char* server_name = argv[1];
  unsigned short port = atoi(argv[2]);

  // Connect to the server
  int socket_fd = socket_connect(server_name, port);
  if (socket_fd == -1) {
    perror("Failed to connect");
    exit(EXIT_FAILURE);
  }

  // Read a message from the server
  char* message = receive_message(socket_fd);
  if (message == NULL) {
    perror("Failed to read message from server");
    exit(EXIT_FAILURE);
  }

  // Print the message
  printf("Server sent: %s\n", message);

  // Free the message
  free(message);
  size_t size = 200;
  char* msg = malloc(sizeof(char) * size);
  // Send a message to the server
  while(1){

    getline(&msg, &size, stdin);
  int rc = send_message(socket_fd, msg);
  if (rc == -1) {
    perror("Failed to send message to server");
    exit(EXIT_FAILURE);
  }
  
  message = receive_message(socket_fd);
  if (message == NULL) {
    perror("Failed to read message from client");
    exit(EXIT_FAILURE);
  }
  printf("Server sent: %s", message);

  if(strcmp(msg, "quit\n") == 0){
    printf("ending\n");
     close(socket_fd);
     free(msg);
     return 0;

  }
  }
  return 0;
}
