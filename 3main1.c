//#define _POSIX_C_SOURCE 199309L
//#define __need_timespec

#include<stdio.h>
#include<time.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>


/*time open read*/
void sys_out(int nbytes,const char *input,const char *output);
void std_out(int nbytes,const char *input,const char *output);
int main()
{
        //sys vs std with nbytes = 1
        sys_out(1,"test_input","test_output");
        std_out(1,"test_input","test_output");
        //sys vs std with nbytes = 1024
        sys_out(1024,"test_input","test_output");
        std_out(1024,"test_input","test_output");
}
void sys_out(int nbytes,const char *input,const char *output)
{
        //set clock
        struct timespec t1;
        struct timespec t2;
        int size = nbytes;
        char file[nbytes];
        int flag1 = open(input,O_RDONLY);
        int flag2 = open(output,O_WRONLY | O_CREAT, 0666);
        if(flag1 == -1) //open error
        {
                printf("Errors! Can't open The intput FIle\n");
                return ;
        }
        if(flag2 == -1)
        {
                printf("Errors! Can't open the output File\n");
                return ;
        }
        clock_gettime(CLOCK_REALTIME,&t1); //get time
        while(1)
        {
                //copy process
                size = read(flag1,file,nbytes);
                if(size == 0)
                {
                        break;
                }
                write(flag2,file,size);
        }

        close(flag1);
        close(flag2);
        clock_gettime(CLOCK_REALTIME,&t2);
        printf("copy&paste(system method) finished with %ld \n",(t2.tv_sec-t1.tv_sec)*1000000 + (t2.tv_nsec-t1.tv_nsec)/1000);

}
void std_out(int nbytes,const char *input,const char *output)
{
        //set clock
        struct timespec t1;
        struct timespec t2;
        size_t size = nbytes;
        char file[nbytes];
        FILE *flag1 = fopen(input,"r");
        FILE *flag2 = fopen(output,"w");
        if(flag1 == -1) //open error
        {
                printf("Errors! Can't open The intput FIle\n");
                return ;                                                                }         
        if(flag2 == -1)
        {
                printf("Errors! Can't open the output File\n");
                return ;
        }
        clock_gettime(CLOCK_REALTIME,&t1); //get time
        while(1)
        {
                //copy process
                size = fread(file,nbytes,1,flag1);
                if(size == 0)
                {
                        break;
                }
                fwrite(file,size,1,flag2);
        }
        close(flag1);
        close(flag2);
        clock_gettime(CLOCK_REALTIME,&t2);
        printf("copy&paste(library method) finished with %ld \n",(t2.tv_sec-t1.tv_sec)*1000000 + (t2.tv_nsec-t1.tv_nsec)/1000);
}

