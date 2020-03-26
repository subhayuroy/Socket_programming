//
// Created by subhayu_roy on 3/26/20.
//

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
int main(int argc, char const *argv[])
{
    int server_fd,new_socket,valread;
    struct sockaddr_in address;
    int opt=1;
    int addrlen = sizeof(address);
    char buffer[1024]= {0};
    char *hello= "Hello from server";
    if((server_fd= socket(AF_INET, SOCK_STREAM,0))==0)  //Creating socket file descriptor
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
    if(setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT, &opt, sizeof(opt)))  //Forcefully attaching socket to the PORT 8080
    {
        perror("Setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr= INADDR_ANY;
    address.sin_port= htons(PORT);
    if(bind(server_fd,(struct sockaddr *)&address, sizeof(address))<0)  //Forcefully attaching socket to the PORT 8080
    {
        perror("Build failed");
        exit(EXIT_FAILURE);
    }
    if(listen(server_fd,3)<0)
    {
        perror("Listen");
        exit(EXIT_FAILURE);
    }
    if((new_socket=accept(server_fd,(struct sockaddr *)&address,(socklen_t *)&address))<0)
    {
        perror("Accept");
        exit(EXIT_FAILURE);
    }
    valread = read(new_socket,buffer,1024);
    printf("%s\n",buffer);
    send(new_socket,hello,strlen(hello),0);
    printf("Hello message sent\n");
    return 0;
}