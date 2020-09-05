#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

// check if it is the same inode on the same device
#define SAME_INODE(a, b) ((a).st_ino == (b).st_ino && (a).st_dev == (b).st_dev)

void moveFile(int argc , char **argv)
{

  struct stat statbuf_src, statbuf_dest;
  char *src, *dest, *new_src, *new_dest;
  char *current_directory;

  if (argc != 3) {    //checking for valid inputs
    fprintf(stderr, "usage: %s src dest\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  // work on copy
  src = malloc(strlen(argv[1]) + 1);
  dest = malloc(strlen(argv[2]) + 1);

  // char* token = strtok(argv[1], "/"); 
	// while (token != NULL) { 
	// 	printf("%s\n", token); 
  //       // dest[i] = token;
  //     token = strtok(NULL, "/"); 

  //   } 
  // dest = malloc(strlen(*token)+1);
  
  strcpy(src, argv[1]);
  strcpy(dest, argv[2]);
  // strcpy(dest, token);
  printf("\n1"); 
  // src = token;
  printf("\n2"); 
  stat(src, &statbuf_src);
  stat(dest, &statbuf_dest);

  if (SAME_INODE(statbuf_dest, statbuf_src)) {
    printf("%s and %s are the identical\n", src, dest);
  }
  
  
  current_directory = getenv("PWD");
  printf("current directory is \"%s\"\n", current_directory);

  
  new_src = malloc(strlen(src) + 1 + strlen(current_directory) + 1);
  strcpy(new_src,current_directory);
  strcat(new_src,"/");
  strcat(new_src,src);

  new_dest = malloc(strlen(dest) + 1 + strlen(current_directory) + 1 + strlen(src) + 1);
  strcpy(new_dest,current_directory);
  strcat(new_dest,"/");
  strcat(new_dest,dest);
  strcat(new_dest,"/");
  strcat(new_dest,src);
  

  if(rename(new_src,new_dest) != 0){
    fprintf(stderr,"rename failed with error %s\n",strerror(errno));
  }

  free(new_src);
  free(new_dest);
  free(src);
  free(dest);

  exit(EXIT_SUCCESS);
}

