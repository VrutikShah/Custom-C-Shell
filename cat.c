#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <unistd.h>
#include<string.h>
#include <fcntl.h>


// takes multiple arguments
void cat(char *argv[])
{
    int fd,r,j=0;
    char temp,line[100];
    int i = 2;
    while(argv[i] != NULL){
        printf("\n%s: \n",argv[i]);
        if((fd=open(argv[i],O_RDONLY)) != -1)   // opens the file descriptor
        {
            while((r=read(fd,&temp,sizeof(char)))!= 0)
            {
                if(temp!='\n')
                {
                    line[j]=temp;
                    j++;
                }
                else
                {
                    printf("%s\n",line);        //prints all lines
                    memset(line,0,sizeof(line));
                    j=0;
                }
            }
        }  
        i++;
    } 
}