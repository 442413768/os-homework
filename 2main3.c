#include<stdio.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<fcntl.h>

/*define keys for memory and signals*/

#define shkey 9996
#define sigkey1 9991
#define sigkey2 9992

/*define size*/
#define ssize 1024
#define msize 256

void semSignal(int sid);
static void semcall(int sid,int op)
{
        struct sembuf semb;
        semb.sem_num = 0;
        semb.sem_op = op;
        semb.sem_flg = 0;
        semop(sid,&semb,1);
}
int creatsem(key_t key)
{
        int sid;
        union un
        {
                int val;
                struct semid *buf;
                ushort *array;
        }arg;
        sid = semget(key,1,0666|IPC_CREAT);
        arg.val = 1;
        semctl(sid,0,SETVAL,arg);
        return sid;
}
void semWait(int sid)
{
        semcall(sid,-1);
}
void semSignal(int sid)
{
        semcall(sid,1);
}
struct text
{
        size_t size;
        char buffer[msize];
};
int main(void)
{
        int seg_id = shmget(shkey,ssize,IPC_CREAT|0666);
        if(seg_id==1)
        {
                printf("shmget error!\n");
                return -1;
        }
        struct text *seg_addr = shmat(seg_id,NULL,0);
        int sid1 = creatsem(sigkey1);
        int sid2 = creatsem(sigkey2);
        semWait(sid2);
        if(fork())
        {
                semWait(sid1);
                int file = open("ori_msg.txt",O_RDONLY);
                size_t result = read(file,seg_addr->buffer,msize);
                if(result<0)
                {
                        printf("read error\n");
                        return -1;
                }
                else
                {
                        seg_addr->size=result;
                        semSignal(sid2);
                }
        }
        else
        {
                semWait(sid2);
                int file = open("new_msg2.txt",O_WRONLY|O_CREAT|O_TRUNC,0777);
                ssize_t result = write(file,seg_addr->buffer,msize);
        }
        shmdt(seg_addr);
        return 0;
}
                                                                           

