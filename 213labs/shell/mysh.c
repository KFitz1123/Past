#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// This is the maximum number of arguments your shell should handle for one command
#define MAX_ARGS 128

char* whitespace_remove();
void execute(char* args[], char delim);

int main(int argc, char** argv) {
  // If there was a command line option passed in, use that file instead of stdin
  if (argc == 2) {
    // Try to open the file
    int new_input = open(argv[1], O_RDONLY);
    if (new_input == -1) {
      fprintf(stderr, "Failed to open input file %s\n", argv[1]);
      exit(1);
    }

    // Now swap this file in and use it as stdin
    if (dup2(new_input, STDIN_FILENO) == -1) {
      fprintf(stderr, "Failed to set new file as input\n");
      exit(2);
    }
  }

  char* line = NULL;     // Pointer that will hold the line we read in
  size_t line_size = 0;  // The number of bytes available in line

  // Loop forever
  while (true) {
    // Print the shell prompt
    printf("$ ");

    // Get a line of stdin, storing the string pointer in line
    if (getline(&line, &line_size, stdin) == -1) {
      if (errno == EINVAL) {
        perror("Unable to read command line");
        exit(2);
      } else {
        // Must have been end of file (ctrl+D)
        printf("\nShutting down...\n");
        break; // Exit infinite loop
      }
    }
    line = whitespace_remove(line);
    char* current_position = line;
    char *token = NULL;
    char * args[MAX_ARGS];
    int i = 0;

    while(true) {
      //printf("current pos 1 = %ps\n", &current_position);
      char* delim_position = strpbrk(current_position, ";&");
      args[0] = "";
      i = 0;
      if (delim_position == NULL) {
        while ((token = strsep(&current_position, " ")) != NULL) {
          args[i] = token;
          i++;
        } // while to sep each arg
        args[i-1][strlen(args[i-1])-1] = '\0';
        args[i] = NULL;
        execute(args, '\0');
        break;
      } else {

         //There was a delimeter. First, save it.
         char delim = *delim_position;
          if(delim == ';'){
        while(strstr(token = strsep(&current_position, " "), ";") == NULL) {
         token = whitespace_remove(token);
          args[i] = token;
          i++;
            } // while to sep each cmd
          args[i] = token;
          i++;
           if(strstr(args[i-1], "\n") != NULL){
             args[i-1][strlen(args[i-1])-2] = '\0';
           }else{
            args[i-1][strlen(args[i-1])-1] = '\0';
           }
        args[i] = NULL;
        execute(args, ';');
        // Move our current position in the string to one character past the delimeter
        current_position = delim_position + 2;
          }//if delim is ;
        else if(delim == '&'){

        while(strstr(token = strsep(&current_position, " "), "&") == NULL) {
         token = whitespace_remove(token);
          args[i] = token;
          i++;
            } // while to sep each cmd
          args[i] = token;
          i++;
           if(strstr(args[i-1], "\n") != NULL){
             args[i-1][strlen(args[i-1])-2] = '\0';
           }else{
            args[i-1][strlen(args[i-1])-1] = '\0';
           }
        args[i] = NULL;
        execute(args, '&');
        // Move our current position in the string to one character past the delimeter
        current_position = delim_position + 2;

        } else{
        printf("something horrible happened here...\n");
        break;
        }
      }// big else

    } // big While


  // If we read in at least one line, free this space
  }

  if (line != NULL) {
    free(line);
  }

  return 0;
}


void execute (char * args[], char delim){
if (strcmp(args[0], "cd") == 0) {
    chdir(args[1]); // change dirs
  } else if (strcmp(args[0], "") == 0) { // empty input
  } else if (strcmp(args[0], "exit") == 0) { // exit
    exit(EXIT_SUCCESS);
  } else {
  //Part B
    int status = 0;
    pid_t ID = fork();
    if (ID < 0) {
      perror ("Fork Failed");
      exit(EXIT_FAILURE);
    }

    if(ID == 0) {
      execvp(args[0], &args[0]);
      perror("exec Failed");
    } else {
      if(delim != '&'){
        pid_t rc = wait(&status);
        if(rc ==-1){
          perror("wait failed\n");
          exit(EXIT_FAILURE);
        }
        printf("[%s exited with status of %d]\n", args[0], WEXITSTATUS(status));
      } // if not &
      else {
        pid_t rc;

        while((rc = waitpid(-1, &status, WNOHANG)) > 0){
          printf("[background process %d exited with status of %d]\n", rc, WEXITSTATUS(status));
        }
      }
    }// inner cond checks
  } // inner else
} //execute


char* whitespace_remove(char* str){
  while(*str == ' '){
    str++;
  }
  return str;
}