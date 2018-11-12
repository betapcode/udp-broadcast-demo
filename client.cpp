//
// Created by Betapcode on 11/6/18.
//

// client.cpp 

#include <iostream>
#include <stdio.h>      
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h> 
#include <string.h> 
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/select.h>

//#include "main.h"


#define PORT 30668
#define MAXLINE 1024 

using namespace std;

int main() {
    
    int sockfd, n; 

    string str = "hello";
    char buffer[MAXLINE]; 
    
    const char *hello = str.c_str();

	struct sockaddr_in servaddr; 

	// Creating socket
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 

    int checkCall;
    int broadcastOn = 1;

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr = INADDR_BROADCAST; 
    servaddr.sin_port=htons(PORT);
 
    checkCall = setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcastOn, 4);
   
    if (checkCall == -1) {
        printf("Error: setsockopt call failed\n");
    }

    socklen_t len = sizeof(servaddr);
    
    sendto(sockfd, (char *)hello, sizeof(hello), 0, (const struct sockaddr *) &servaddr, sizeof(servaddr)); 
    
    while(1)
    {
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 
        buffer[n] = '\0'; 
        printf("Server : %s\n", buffer); 
        //cout << " + n: " << n << " - flag: "<< len << endl;

        printf("\n- %s:%d",inet_ntoa(servaddr.sin_addr),ntohs(servaddr.sin_port));
        
        fflush(stdout);

    
        fd_set socks;
        struct timeval t;
        FD_ZERO(&socks);
        FD_SET(sockfd, &socks);
        t.tv_sec = 3;
        if (!select(sockfd + 1, &socks, NULL, NULL, &t))
        {
            //cout << "\nHết dữ liệu rồi " << endl;
            break;
        }
    }
    
    return 0;
}
