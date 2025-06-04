#define _GNU_SOURCE
#include <openssl/md5.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_USERNAME_LENGTH 64
#define PASSWORD_LENGTH 6
#define INIT_LIST 300
#define QUARTER 77228944

/************************* Part A *************************/

//    **type in every new terminal ***
//export LD_LIBRARY_PATH=/home/curtsinger/.local/lib
//./password-cracker

int list_length = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int cracked = 0;
int maxlen = INIT_LIST;


/**
 * Find a six character lower-case alphabetic password that hashes
 * to the given hash value. Complete this function for part A of the lab.
 *
 * \param input_hash  An array of MD5_DIGEST_LENGTH bytes that holds the hash of a password
 * \param output      A pointer to memory with space for a six character password + '\0'
 * \returns           0 if the password was cracked. -1 otherwise.
 */
int crack_single_password(uint8_t* input_hash, char* output) {
  // Take our candidate password and hash it using MD5
  char candidate_passwd[PASSWORD_LENGTH + 1] = "aaaaaa"; //<holds the password we are trying
  int lastdigit = 0;
  int next = 1;

uint8_t candidate_hash[MD5_DIGEST_LENGTH]; //< This will hold the hash of the candidate password

//MD5((unsigned char*)"zzzzza", strlen(candidate_passwd), input_hash); //< Do the hash

  while(1){
  next = 1;

  while(next == 1){
  if(candidate_passwd[lastdigit] == 'z'){
    candidate_passwd[lastdigit]  = 'a';
    lastdigit++;
  } else {
    candidate_passwd[lastdigit]++;
    next = 0;
    lastdigit = 0;
    }
  }

  MD5((unsigned char*)candidate_passwd, strlen(candidate_passwd), candidate_hash); //< Do the hash

  // Now check if the hash of the candidate password matches the input hash
  if(memcmp(input_hash, candidate_hash, MD5_DIGEST_LENGTH) == 0) {
    // Match! Copy the password to the output and return 0 (success)
    strncpy(output, candidate_passwd, PASSWORD_LENGTH+1);
    return 0;
  } else {
    // No match. Return -1 (failure)
  }
  }
  return -1;
}

/********************* Parts B & C ************************/

/**
 * This struct is the root of the data structure that will hold users and hashed passwords.
 * This could be any type of data structure you choose: list, array, tree, hash table, etc.
 * Implement this data structure for part B of the lab.
 */
typedef struct password_set {
  // You will need to fill in fields here
  char* IDs[INIT_LIST];
  uint8_t* hashes[INIT_LIST];
  int maxlength;
  int nextempty;
} password_set_t;



/**
 * Initialize a password set.
 * Complete this implementation for part B of the lab.
 *
 * \param passwords  A pointer to allocated memory that will hold a password set
 */
void init_password_set(password_set_t* passwords) {
  passwords->nextempty = 0;
  char candidate_passwd[6] = "aaaaaa";

  for(int i = 0; i < (QUARTER * 4); i++){
    
  int next = 1;
  int lastdigit = 0;

  while(next == 1){
  if(candidate_passwd[lastdigit] == 'z'){
    candidate_passwd[lastdigit]  = 'a';
    lastdigit++;
  } else {
    candidate_passwd[lastdigit]++;
    next = 0;
    lastdigit = 0;
    }

  }

  }
  for(int i = 0; i < 6; i++){
    printf("%c", candidate_passwd[i]);
  }
  printf("\n");
//exit(0);
  //create right array size
}

void expand_pass_arr(password_set_t* oldpass){
  char* new_ID_arr[oldpass->nextempty * 2];
  uint8_t* new_hash_arr[oldpass->nextempty * 2];
  for(int i = 0; i < oldpass->nextempty; i++){
    new_ID_arr[i] = oldpass->IDs[i];
    new_hash_arr[i] = oldpass->hashes[i];
  }

}

/**
 * Add a password to a password set
 * Complete this implementation for part B of the lab.
 *
 * \param passwords   A pointer to a password set initialized with the function above.
 * \param username    The name of the user being added. The memory that holds this string's
 *                    characters will be reused, so if you keep a copy you must duplicate the
 *                    string. I recommend calling strdup().
 * \param password_hash   An array of MD5_DIGEST_LENGTH bytes that holds the hash of this user's
 *                        password. The memory that holds this array will be reused, so you must
 *                        make a copy of this value if you retain it in your data structure.
 */
void add_password(password_set_t* passwords, char* username, uint8_t* password_hash) {

  char* saved_user = strdup(username);
  uint8_t* saved_pass = malloc(sizeof(uint8_t) * MD5_DIGEST_LENGTH);

  memcpy(saved_pass, password_hash, (size_t) MD5_DIGEST_LENGTH);

  if(passwords->nextempty > maxlen) expand_pass_arr(passwords);
  passwords->IDs[passwords->nextempty] = saved_user;
  passwords->hashes[passwords->nextempty] = saved_pass;
  passwords->nextempty++;
  list_length++;

}

typedef struct list_Start{
  char* startval;
  password_set_t* passwords;
}list_Start_t;
/**
 * Crack all of the passwords in a set of passwords. The function should print the username
 * and cracked password for each user listed in passwords, separated by a space character.
 * Complete this implementation for part B of the lab.
 *
 * \returns The number of passwords cracked in the list
 */

 void * cracknum(void* start);

int crack_password_list(password_set_t* passwords) {

  pthread_t threads[4];

    for(int i = 0; i < 4; i++){
  list_Start_t* input = malloc(sizeof(list_Start_t));
  switch(i){
    case(0):
      input->startval = "aaaaaa";
      break;
     case(1):
       input->startval = "aaaang";
       break;
     case(2):
      input->startval = "aaaaan";
      break;
     case(3):
       input->startval = "aaaant";
      break;
    default:;
  }
  input->passwords= passwords;
  int success = pthread_create(&threads[i], NULL, cracknum, input);
    if(success ==1){
    perror("thread creation failed");
    exit(EXIT_FAILURE);
    }
   //cracknum((void*) input);
    }


for(int i = 0; i < 1; i++){
  pthread_join(threads[i],NULL);
}

  return cracked;
}



void* cracknum(void* start){
list_Start_t* pass_struct = (list_Start_t*) start;
char candidate_passwd[PASSWORD_LENGTH + 1];
//make it a 'string' array
for(int i = 0; i < PASSWORD_LENGTH; i++){
candidate_passwd[i] = *(pass_struct->startval + i);
}
candidate_passwd[PASSWORD_LENGTH] = '\0';

//<holds the password we are trying
  int lastdigit = 0;
  int next = 1;
  int tried = 0;

uint8_t candidate_hash[MD5_DIGEST_LENGTH];
while(tried <= QUARTER){
  next = 1;

  while(next == 1){
  if(candidate_passwd[lastdigit] == 'z'){
    candidate_passwd[lastdigit]  = 'a';
    lastdigit++;
  } else {
    candidate_passwd[lastdigit]++;
    next = 0;
    lastdigit = 0;
    }

  }


MD5((unsigned char*)candidate_passwd, strlen(candidate_passwd), candidate_hash); //< Do the hash
  for(int i = 0; i < pass_struct->passwords->nextempty; i++){
  // Now check if the hash of the candidate password matches the input hash

  if(memcmp(pass_struct->passwords->hashes[i], candidate_hash, MD5_DIGEST_LENGTH) == 0) {
    // Match! Copy the password to the output and return 0 (success)
    printf("%s %s\n",pass_struct->passwords->IDs[i],candidate_passwd);
    pthread_mutex_lock(&lock);
    cracked++;
    pthread_mutex_unlock(&lock);
    }
  }
  tried++;
}
  return start;
}
/******************** Provided Code ***********************/

/**
 * Convert a string representation of an MD5 hash to a sequence
 * of bytes. The input md5_string must be 32 characters long, and
 * the output buffer bytes must have room for MD5_DIGEST_LENGTH
 * bytes.
 *
 * \param md5_string  The md5 string representation
 * \param bytes       The destination buffer for the converted md5 hash
 * \returns           0 on success, -1 otherwise
 */
int md5_string_to_bytes(const char* md5_string, uint8_t* bytes) {
  // Check for a valid MD5 string
  if(strlen(md5_string) != 2 * MD5_DIGEST_LENGTH) return -1;

  // Start our "cursor" at the start of the string
  const char* pos = md5_string;

  // Loop until we've read enough bytes
  for(size_t i=0; i<MD5_DIGEST_LENGTH; i++) {
    // Read one byte (two characters)
    int rc = sscanf(pos, "%2hhx", &bytes[i]);
    if(rc != 1) return -1;

    // Move the "cursor" to the next hexadecimal byte
    pos += 2;
  }

  return 0;
}

void print_usage(const char* exec_name) {
  fprintf(stderr, "Usage:\n");
  fprintf(stderr, "  %s single <MD5 hash>\n", exec_name);
  fprintf(stderr, "  %s list <password file name>\n", exec_name);
}

int main(int argc, char** argv) {
  if(argc != 3) {
    print_usage(argv[0]);
    exit(1);
  }

  if(strcmp(argv[1], "single") == 0) {

    // The input MD5 hash is a string in hexadecimal. Convert it to bytes.
    uint8_t input_hash[MD5_DIGEST_LENGTH];
    if(md5_string_to_bytes(argv[2], input_hash)) {
      fprintf(stderr, "Input has value %s is not a valid MD5 hash.\n", argv[2]);
      exit(1);
    }

    // Now call the crack_single_password function
    char result[7];
    if(crack_single_password(input_hash, result)) {
      printf("No matching password found.\n");
    } else {
      printf("%s\n", result);
    }

  } else if(strcmp(argv[1], "list") == 0) {
    // Make and initialize a password set
    password_set_t passwords;
    init_password_set(&passwords);

    // Open the password file
    FILE* password_file = fopen(argv[2], "r");
    if(password_file == NULL) {
      perror("opening password file");
      exit(2);
    }

    int password_count = 0;

    // Read until we hit the end of the file
    while(!feof(password_file)) {
      // Make space to hold the username
      char username[MAX_USERNAME_LENGTH];

      // Make space to hold the MD5 string
      char md5_string[MD5_DIGEST_LENGTH * 2 + 1];

      // Make space to hold the MD5 bytes
      uint8_t password_hash[MD5_DIGEST_LENGTH];

      // Try to read. The space in the format string is required to eat the newline
      if(fscanf(password_file, "%s %s ", username, md5_string) != 2) {
        fprintf(stderr, "Error reading password file: malformed line\n");
        exit(2);
      }

      // Convert the MD5 string to MD5 bytes in our new node
      if(md5_string_to_bytes(md5_string, password_hash) != 0) {
        fprintf(stderr, "Error reading MD5\n");
        exit(2);
      }

      // Add the password to the password set
      add_password(&passwords, username, password_hash);
      password_count++;
    }

    // Now run the password list cracker
    int cracked = crack_password_list(&passwords);

    printf("Cracked %d of %d passwords.\n", cracked, password_count);

  } else {
    print_usage(argv[0]);
    exit(1);
  }

  return 0;
}
