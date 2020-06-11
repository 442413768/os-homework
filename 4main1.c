#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/io.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>
#define output_file "test_output"

char *host_name = "127.0.0.1";
int port = 12345;

void main()
{
        int cliaddr_len;
        char recvbuf[256],sendbuf[256];
        int sockfd;
        int sequence = 0;
        struct sockaddr_in servaddr,cliaddr;
        struct hostent *shost_name;
        if((shost_name = gethostbyname(host_name))==0)
                printf("ERRORS! resolving local host");
        bzero(&servaddr,sizeof(servaddr));

        FILE *flag2 = fopen(output_file,"w");
        if(flag2==NULL)
        {
                printf("error while open output file");
                exit(0);
        }
        //printf("No Problem!");
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(port);
        if((sockfd = socket(AF_INET,SOCK_DGRAM,0))==-1)
                printf("ERROR! Opening socket");
        if(bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0)
                printf("Call to bind");
        while(1)
        {
                flag2 = fopen(output_file,"aw");
                cliaddr_len = sizeof(cliaddr);
                int ret = recvfrom(sockfd,recvbuf,256,0,(struct sockaddr *)&cliaddr,&cliaddr_len);
                if(ret==-1){
                        printf("ERROR!while receiving response");
                }
                printf("d = %d\n",ret)
                sprintf(sendbuf,"ACK: %s\n",recvbuf);
                sendto(sockfd,sendbuf,256,0,(struct sockaddr *)&cliaddr,cliaddr_len);//send data
                fwrite(recvbuf,ret,1,flag2);
                fclose(flag2);
                //printf(recvbuf);
                //fwrite(recvbuf,sizeof(recvbuf),1,flag2);
                
        }
        close(sockfd);
        //fclose(flag2);
}
              
                                                                  
