#include<sys/msg.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/ipc.h>

#define msgkey 9996
#define msgsize 256

struct content
{
        size_t size;
        char buf[msgsize];
};
struct msg
{
        int mtype;
        struct content text;
};
int main(void)
{
        struct msg buf1;
        int qid = msgget(msgkey,IPC_CREAT|0666);
        if (qid==-1)
        {
                printf('msgget error!\n');
                return -1;
        }
        int pid = 0;
        while((pid=fork())==-1);
        if(pid)
        {
                msgrcv(qid,&buf1,msgsize,1,MSG_NOERROR);
                int newfile = open("newmsg.txt",O_WRONLY | O_CREAT|O_TRUNC,0777);
                size_t result = write(newfile,buf1.text.buf,msgsize);
                if(result<0)
                {
                        printf("write error\n");
                        return 0;
                }
        }
        else
        {
                buf1.mtype = 1;
                int file = open("ori_msg.txt",O_RDONLY);
                size_t result = read(file,buf1.text.buf,msgsize);
                if(result<0)
                {
                        printf("read error\n");
                        return 0;
                }
                buf1.text.size = result;
                int lentext = sizeof(buf1.text);
                msgsnd(qid,&buf1,lentext,0);
        }
        return 0;
}

