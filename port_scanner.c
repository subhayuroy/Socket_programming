//
// Created by subhayu_roy on 3/26/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
struct sockaddr_in dest;

int main()
{
    int msocket,con,port;
    printf("Enter the number of ports= ");
    scanf("%d",&port);
    if((msocket = socket(AF_INET, SOCK_STREAM,0))==-1)
    {
        perror("socket");
        exit(1);
    }
    dest.sin_family=AF_INET;
    dest.sin_port= htons(port);
    bzero(dest.sin_zero, sizeof(dest.sin_zero));
    if((con= connect(msocket,(struct sockaddr *)&dest, sizeof(dest)))== -1)
    {
        perror("Connect");
        close(msocket);
        exit(1);
    } else
    {
        printf("%d Open. \n",port);
        exit(1);
    }
    return 0;
}