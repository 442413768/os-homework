#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<sys/io.h>
#include<unistd.h>


//#define NPACK 5
#define file_input "test_input"


int port =  12345;
void main()
{
        // 1. input
        // 2. store the output recvbuf 
        int sockfd, n;
        int sequence = 0;
        char sendbuf[256], recvbuf[256];  //buffer for receiver and sender
        struct sockaddr_in addr;
        sockfd = socket(AF_INET,SOCK_DGRAM,0);
        if(sockfd == -1)
                printf("Opening Socket!");
        memset(&addr,0,sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        addr.sin_port = htons(port);

        FILE* flag1 = fopen(file_input,"r");

        char term = ';';
        int i=0;
        while( i<256)
        {
                fscanf(flag1,"%s",&sendbuf[i]);
                if((sendbuf[i])==term)             //method1 success
                        break;
                i++;
        }
        //printf("i = %d",i);   
        //printf(sendbuf);
        if(sendto(sockfd,sendbuf,i,0,(struct sockaddr *)&addr,sizeof(addr))<0)
                printf("Trying to sento\n");
        int len  = recvfrom(sockfd,recvbuf,sizeof(recvbuf),0,NULL,NULL);
        //printf("d = %d \n ",len);
        recvbuf[len] = 0;
        //printf("the following message was received: \n");

        fputs(recvbuf,stdout);

        /*      
        for(sequence=0;sequence<NPACK;sequence++){
                sprintf(sendbuf,"data packet with sequence %d\n",sequence);
                if(sequence ==NPACK)
                {
                        sprintf(sendbuf,"stop\n");
                        break;
                }
                if(sendto(sockfd,sendbuf,sizeof(sendbuf),0,(struct sockaddr *)&addr,sizeof(addr))<0)
                        printf("Trying to sento");
                n = recvfrom(sockfd,recvbuf,sizeof(recvbuf),0,NULL,NULL);
                recvbuf[n] = 0;
                //fputs(recvbuf,stdout);
        }
        */
        close(sockfd);
