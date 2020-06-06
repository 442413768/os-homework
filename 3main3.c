#include<stdio.h>
#include<sys/io.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
        char buf[100];
        int chan[2];
        char *input = "test_input";
        char *output = "test_output";
        int flag = pipe(chan);
        if(flag==-1)
        {
                printf("ERRORS! Cant't creat pipe \n");
                return 0;
        }
        if(fork())
        {
                // Father Process
                close(chan[0]);
                int flago = open(input,O_RDONLY);       //const O_RDONLY:mode 
                if(flago == -1)
                {
                        printf("Errors! Can't open the input file\n");
                        return 0;
                }

                while(1)
                {
                        int flagw = read(flago,buf,100);
                        if(flagw==0)
                        {
                                break;
                        }
                        write(chan[1],buf,flagw);
                }
                close(flago);
                close(chan[1]);
        }
        else
        {
                //child process
                close(chan[1]);
                int flago = open(output,O_WRONLY | O_CREAT,0666);
                if(flago ==-1)
                {
                        printf("ERRORS! Can't open the output file\n");
                        return 0;
                }
                while(1)
                {
                        int flagr = read(chan[0],buf,100);
                        if(flagr==0)
                        {
                                break;
                        }
                        flagr = write(flago,buf,flagr);
                }
                close(chan[0]);
        }
        return 0;
}
