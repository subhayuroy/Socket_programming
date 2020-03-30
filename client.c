//
// Created by subhayu_roy on 3/26/20.
//
//
//#include <stdio.h>
//#include <sys/socket.h>
//#include <arpa/inet.h>
//#include <unistd.h>
//#include <string.h>
//#define PORT 8080
//int main(int argc, char const *argv[])
//{
//    int sock = 0,valread;
//    struct sockaddr_in serv_addr;
//    char *hello= "Hello from Client";
//    char buffer[1024] = {0};
//    if((sock = socket(AF_INET,SOCK_STREAM,0))<0)
//    {
//        printf("\nSocket creation error\n");
//        return -1;
//    }
//    serv_addr.sin_family=AF_INET;
//    serv_addr.sin_port=htons(PORT);
//    if(inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr)<=0)  //Convert IPv4 and IPv6 address from text to binary form
//    {
//        printf("\nInvalid address/Address not supported\n");
//        return -1;
//    }
//    if(connect(sock,(struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
//    {
//        printf("\nConnection Failed\n");
//        return -1;
//    }
//    send(sock,hello,strlen(hello),0);
//    printf("Hello message sent\n");
//    valread= read(sock,buffer,1024);
//    printf("%s\n",buffer);
//    return 0;
//}



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[255];

    if (argc <3)
    {
        fprintf(stderr,"usage %s hostname port\n",argv[0]);
        exit(1);
    }

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0)
        error("Opening socket\n");

    server = gethostbyname(argv[1]);
    if(server == NULL)
        fprintf(stderr,"Error, no such host\n");

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)&server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);

    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
        error("Connection failed\n");

    while (1)
    {
        bzero(buffer,255);
        fgets(buffer,255,stdin);
        n = write(sockfd,buffer,strlen(buffer));
        if(n<0)
            error("Error on writing\n");

        bzero(buffer,255);
        n= read(sockfd,buffer, 255);
        if (n<0)
            error("Error on reading\n");
        printf("Server : %s\n",buffer);
        int i = strncmp("Bye", buffer, 3);
        if(i==0)
            break;
    }

    close(sockfd);
    return 0;
}