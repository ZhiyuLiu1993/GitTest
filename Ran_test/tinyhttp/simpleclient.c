//
// Created by root on 5/17/18.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
//    char ch = 'A';

    sleep(5);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_port = htons(80);
    //inet_addr应该换为inet_pton  支持IpV4和IpV6
    //if(inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) == -1)
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    len = sizeof(address);

    result = connect(sockfd, (struct sockaddr *)&address, len);

    if(result == -1){
        perror("oops: client1");
        exit(1);
    }
    char buf[1024];

    sprintf(buf, "GET /");
    send(sockfd, buf, sizeof(buf), 0);

    ssize_t nread;
    while((nread = read(sockfd, buf, sizeof(buf))) != 0)
        printf("char from sever = %s\n", buf);
    close(sockfd);
    exit(0);
}