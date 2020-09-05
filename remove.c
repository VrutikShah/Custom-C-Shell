#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int rm (char *argv[]) {
   int ret;
   FILE *fp;
   char *filename = malloc(strlen(argv[1]) + 1);
    strcpy(filename,argv[1]);

   ret = remove(filename);

   if(ret == 0) {
      printf("File deleted successfully");
   } else {
      printf("Error: unable to delete the file");
   }
   
   return(0);
}
