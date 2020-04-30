#include<stdlib.h>
#include<stdio.h>
void main()
{
        int i,pid,status = 1;
        while((i=fork())==-1);
        if(i)
                {
                        printf("parent process in\n");
                        pid = wait(&status);
                        printf("child process %d, status = %d\n",pid,status);
                }
        else
                {
                        printf("child process in\n");
                        execl("/bin/ls","ls","-l",(char*)0);//image change
                        printf("excel error. \n");
                        exit(2);

                }
printf("parent process done \n");
}
