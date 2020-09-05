#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>



static int background(){
    pid_t pid;
    
    /* Fork parent process */
    pid = fork();
    
    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);
    
     //Success: Let the parent terminate
    if (pid > 0)
        return 1; //to continue
    
    //The child process becomes session leader
    if (setsid() < 0)
        exit(EXIT_FAILURE);
    

    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);
    
    sleep(3);
    return 0;
}