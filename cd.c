#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define MAXLEN 100

void chDir(char * dir[]){
    char *cwd;
    char buf[MAXLEN];
    char *tempdest;
    char *destDir;
    char *token;
    cwd = getcwd(buf,sizeof(buf));
    printf("\nCWD: %s",cwd);
    
    if (dir[1] == ".."){
        token = strtok(cwd,"/");        //tokenising the address
    }
    else{
        tempdest = strcat(cwd,"/");     //building new address
        destDir = strcat(tempdest,dir[1]);
        chdir(destDir);                 //changing dir
    }
    cwd = getcwd(buf,sizeof(buf));
    printf("\nCWD: %s",cwd);

}

