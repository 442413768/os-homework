#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>


#define NAME "fifo"
int main()
{
        //printf("in!");
        char buf[1024];

        //printf("before creat channel");
        mknod(NAME,S_IFIFO | 0666, 0); //set both can read/write
        //printf("after mknod");
        int size = 0;
        int flag1 = open(NAME,O_WRONLY);
        int flag2 = open("test_input",O_RDONLY);
        //printf("after open");
        while(1)
        {
                //printf("outside");
                size = read(flag2,buf,1024);
                if(size ==0)
                {
                        //printf("inside");
                        break;
                }
                write(flag1,buf,size);
        }
        close(flag1);
        close(flag2);

        return 0;

}
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#define NAME "fifo"

int main()
{
        char buf[1024];
        int size = 0;
        int flag1 = open(NAME ,O_RDONLY);
        int flag2 = open("test_output",O_WRONLY | O_CREAT, 0666);
        while(1)
        {
                size = read(flag1 ,buf , sizeof(buf));
                if(size==0)
                {
                        break;
                }
                write(flag2,buf,size);
        }
        close(flag1);
        close(flag2);
        return 0;
}
