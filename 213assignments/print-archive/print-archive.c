#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



void print_contents(uint8_t* data, size_t size);
int print_helper(uint8_t* position);

int main(int argc, char** argv) {
  // Make sure we have a file input
  if (argc != 2) {
    fprintf(stderr, "Please specify an input filename.\n");
    exit(1);
  }

  // Try to open the file
  FILE* input = fopen(argv[1], "r");
  if (input == NULL) {
    perror("Unable to open input file");
    exit(1);
  }

  // Seek to the end of the file so we can get its size
  if (fseek(input, 0, SEEK_END) != 0) {
    perror("Unable to seek to end of file");
    exit(2);
  }

  // Get the size of the file
  size_t size = ftell(input);

  // Seek back to the beginning of the file
  if (fseek(input, 0, SEEK_SET) != 0) {
    perror("Unable to seek to beginning of file");
    exit(2);
  }

  // Allocate a buffer to hold the file contents. We know the size in bytes, so
  // there's no need to multiply to get the size we pass to malloc in this case.
  uint8_t* data = malloc(size);

  // Read the file contents
  if (fread(data, 1, size, input) != size) {
    fprintf(stderr, "Failed to read entire file\n");
    exit(2);
  }

  // Make sure the file starts with the .ar file signature
  if (memcmp(data, "!<arch>\n", 8) != 0) {
    fprintf(stderr, "Input file is not in valid .ar format\n");
    exit(1);
  }

  // Call the code to print the archive contents
  print_contents(data, size);

  // Clean up
  free(data);
  fclose(input);

  return 0;
}

/**
 * This function should print the name of each file in the archive followed by its contents.
 *
 * \param data This is a pointer to the first byte in the file.
 * \param size This is the number of bytes in the file.
 */
void print_contents(uint8_t* data, size_t size) {
  
int ARCHIVEFILE_SIZE = 8; 
size_t scanned_size = 0;
uint8_t* position = data + ARCHIVEFILE_SIZE;
uint8_t* initpos = position;
while((scanned_size + ARCHIVEFILE_SIZE) < size){
  scanned_size += print_helper(position);
  position = initpos + scanned_size;
  }
}


int print_helper(uint8_t* position){
 int IDENTIFIER_SIZE = 16;
 int TIMESTAMP_SIZE = 12;
 int OID_SIZE = 6;
 int GID_SIZE = 6;
 int MODE_SIZE = 8;
 int FILESIZE_SIZE = 10;
 int END_SIZE = 2;
 int HEADER_TOTAL = 60;
  int i = 0;
  while(*(position + i) != '/' && i<15){
    printf("%c", *(position + i));
    i++;
  }
  printf("\n");
  // move past Identifier + Mod Timestamp + OID + GID + Mode
  position = position + IDENTIFIER_SIZE + TIMESTAMP_SIZE + OID_SIZE + GID_SIZE + MODE_SIZE;

  //Store Size
  char filesize_str[11];
  filesize_str[10] = '\0';
  int j = 0;
  while(*(position + j) != ' ' && j<10){
    filesize_str[j] = *(position + j);
    j++;
  }
  filesize_str[j] = '\0';
  int filesize = atoi(filesize_str);

  //move past size + end char
  position = position + FILESIZE_SIZE + END_SIZE;
  for (int k = 0; k < filesize; k++){
    printf("%c", *(position + k));
  } // print data
  printf("\n");

  if((HEADER_TOTAL + filesize) % 2 == 1) {
      position++;
      filesize++;
    }//move past potential extra buffer
  return HEADER_TOTAL + filesize;

}
