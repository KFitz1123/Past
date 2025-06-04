#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void list_directory(const char* directory_name);
int* bitarr(int num);

int main(int argc, char** argv) {
  // Process arguments
  if (argc == 1) {
    list_directory(".");
  } else if (argc == 2) {
    list_directory(argv[1]);
  } else {
    fprintf(stderr, "Please specify one or zero command line arguments.\n");
  }

  return 0;
}

void list_directory(const char* directory_name) {
  DIR* currentdir = opendir(directory_name);
    char loc[100];
    char buffer[100];
    int i = 0;
     while(*(directory_name + i) != '\0'){
      loc[i] = *(directory_name + i);
      i++;
     }
     loc[i] = '/';
     loc[i + 1] = '\0';

  if(currentdir == NULL){
    perror("Directory does not exist. Try again");
  }
  struct dirent* file;
  struct stat stat1;
  char* name;
  char* fullpath = buffer;
  errno = 0;
  while((file = readdir(currentdir)) != NULL){
    strcpy(fullpath, loc);
    name = file->d_name;
    strcat(fullpath, name);
    int e = stat(fullpath, &stat1);
    if(e == -1){
      printf("name of failed reach is %s\n", name);
      printf("%d\n", errno);
      printf("EACCES = %d\n", EACCES);
    printf("EIO = %d\n", EIO);
    printf("ENOENT = %d\n", ENOENT);
    printf("ELOOP = %d\n", ELOOP);

      perror("stat failed\n");
    }
    if(S_ISDIR(stat1.st_mode) != 0){
      printf("d");
      }else{printf("-");
      }

  int arr[16] = {0};
  int i = 0;
  int j = 0;
  int num = (int)stat1.st_mode;
    while(num > 0){
      arr[15 - i] = num % 2;
      num = num / 2;
      i++;
  }

  char permission[3] = {'r','w','x'};

    for(int i = 7; i < 16; i++){
      if(arr[i] == 1){
      printf("%c", permission[j % 3]);
      }else{printf("-");
      }
      j++;
    }

  struct passwd* uid = getpwuid(stat1.st_uid);
  printf(" %s", uid->pw_name);

  struct group* gid = getgrgid(stat1.st_gid);
  printf(" %s", gid->gr_name);

  printf(" %u", (int) stat1.st_size);

  printf(" %s\n", name);



  }
  if(errno != 0){
  printf("errno is %d", errno);
  }
  closedir(currentdir);
}





