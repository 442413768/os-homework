#include<sys/types.h>
#include<signal.h>
#include<stdlib.h>
#include<stdio.h>

void func1();
void main()
{
        int i,pid,status = 1;

        signal(SIGUSR1,func1);
        while((i=fork())==-1);
        if(i)
                {
                        printf("parent process in\n");
                        printf("sending signal\n");
                        kill(pid,SIGUSR1);
                        pid = wait(&status);
                        printf("child process %d, status = %d\n",pid,status);
                }
        else
                {
                        sleep(2);
                        printf("child process in\nsignal received \n");
                        execl("/bin/ls","ls","-l",(char*)0);
                        printf("excel error. \n");
                        exit(2);

                }
printf("parent process done \n");
}

void func1()
{
        printf("It is signal processing function.\n");
}
~                                                                                                    
~        
