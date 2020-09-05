#define _GNU_SOURCE 1
// #define _BSD_SOURCE 1
// #define _SVID_SOURCE 1
#define _DEFAULT_SOURCE 1

#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<readline/readline.h> 
#include<readline/history.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<dirent.h>

#include "makedir.c"
#include "grepp.c"
#include "mv.c"
#include "cd.c"
#include "cat.c"
#include "cp.c"
#include "remove.c"
#include "call.c"


// Defining max length of list and commands  
#define COMMLEN 100
#define LISTLEN 100


void showPreview(){

    system("clear");

    printf("\n********************************"); 
    printf("\n\t****MY SHELL****");
    printf("\n********************************");
    printf("\n");
    sleep(2);

    system("clear");
}


// Function to list all directories - with or without arguments
void ls(char** mainArgs){
    struct dirent **filelist;
    int n = 0;
    int t;
    for (int j = 0;j<LISTLEN;j++){
        if(mainArgs[j] == NULL) break;
        n = n+1;
    }
    if (n == 1){
        t = scandir(".",&filelist,NULL,alphasort);
        t--;
        while(t>=2){
            printf("\n%s",filelist[t]->d_name);
            free(filelist[t]);
            t--;
        }
        free(filelist);
        
    }
    else if(n >= 2){
        
        for (int i = 1;i<n;i++){
            t = scandir(mainArgs[i],&filelist,NULL,alphasort);
            printf("\n\n%s: \n",mainArgs[i]);
            t--;
            while(t>=2){
                printf("\n%s",filelist[t]->d_name);
                free(filelist[t]);
                t--;
            }
            free(filelist);
        }
    }
    else{
        printf("\nINCORRECT INPUT FORMAT. \n'ls' only takes zero or one argument: nothing or Directory name\n");
    }
}

int validInput(char* str){
// Initialises the buffer and reads the input
    char* buf; 
    buf = readline("\ncshell>>> "); 
    if (strlen(buf) != 0) { 
        add_history(buf);    //adds to the history of the shell.User can use arrow keys to interact
        strcpy(str, buf); 
        return 0;
    } else { 
        return 1; 
        printf("exiting input\n");
    }
}


void parseNormal(char* str, char** mainArgs) 
{ 
    int i; 
  
    for (i = 0; i < 100; i++) { 
        mainArgs[i] = strsep(&str, " "); 
  
        if (mainArgs[i] == NULL) 
            break; 
        if (strlen(mainArgs[i]) == 0) 
            i--; 
    } 
} 


void match_pattern(char * argv[]); //Declaring one of the functions called from another file


int main(){
    while(1){                   // main loop
        char str[100];          // stores input 
        char *mainArgs[100];    // stores all the parsed arguments
        if(validInput(str)){
            continue;
        }      
        parseNormal(str,mainArgs);

        int k;                  //stores number of arguments
        for (k = 0; k<LISTLEN;k++){
            if (mainArgs[k] == NULL){
                break;
            }
        }
        
        int parentCheck = 0;    //flag to check if the process is a parent process or child
        int bgCheck = 1;
        bgCheck = strcmp(mainArgs[k-1],"&");
        if(bgCheck == 0){

            parentCheck = background();
            mainArgs[k-1] = NULL;
            k--;
        }

        if(parentCheck == 1){

            continue;
        }

        int numOfComms = 10;
        int commSwitch = 11;
        char direc[512];
        char* listOfComms[numOfComms];

        listOfComms[0] = "pwd";
        listOfComms[1] = "ls";
        listOfComms[2] = "mkdir";
        listOfComms[3] = "grep";
        listOfComms[4] = "cd";
        listOfComms[5] = "mv";
        listOfComms[6] = "cat";
        listOfComms[7] = "cp";
        listOfComms[9] = "rm";
        listOfComms[8] = "chmod";
    
        int i;
        for (i = 0;i<numOfComms;i++){
            if(strcmp(mainArgs[0],listOfComms[i]) == 0){
                commSwitch = i+1;               //selecting the command from the list of Commands
                break;
            }
        }

        pid_t pid,wpid;
        int status;
        switch(commSwitch){
        case 1:
            getcwd(direc,sizeof(direc));
            printf("\nPresent Working Directory is: %s\n",direc);
            break;
        case 2:
            ls(mainArgs);
            break;
        case 3:
            for (int j = 1;j<LISTLEN;j++){
                if(mainArgs[j] == NULL) break;
                makeDir(mainArgs[j]);           
            }       
            break;
        case 4:
            match_pattern(mainArgs);
            break;
        case 5:
            chDir(mainArgs);
            break;
        case 6:
            moveFile(k,mainArgs);
            break;
        case 7:
            cat(mainArgs);
            break;
        case 8:
            copyFile(k, mainArgs);
            break;
        case 9:
            if (k != 3){
                printf("Invalid command. Usage: chmod 0777 filename");
                break;
            }
            if( chmod(mainArgs[2],atoi(mainArgs[1])) == -1 ) {
                perror( mainArgs[2] );     
            }
            break;   
        case 10:
            rm(mainArgs);
            break;
        default:
            // this part is executed when the list of above commands are exhausted. The built-in binaries are used
            // Also provides access to HELP
            pid = fork();
            if (pid == 0) {
            // Child process
                if (execvp(mainArgs[0], mainArgs) == -1) {
                    perror("lsh");
                }
                exit(EXIT_FAILURE);
            } 
            else if (pid < 0) {
                // Error forking
                perror("lsh");
            } 
            else {
            // Parent process
                do {   
                wpid = waitpid(pid, &status, WUNTRACED);
                } while (!WIFEXITED(status) && !WIFSIGNALED(status));
            }
            break;

        }  

        if (parentCheck == 0 && bgCheck == 0){
            exit(EXIT_SUCCESS);         //if its a child process, the process must be terminated here
        }
        
    }
}