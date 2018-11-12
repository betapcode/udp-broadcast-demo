//
// Created by Betapcode on 11/6/18.
//

// server.cpp 

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 30668
#define MAXLINE 1024 

using namespace std;

int main() {
    
    struct sockaddr_in servaddr, cliaddr; 
    int sockfd; 

    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
        printf("bind failed");
		// exit(EXIT_FAILURE); 
	} 

    // begin: define for broadcast
    int _n;
    string _hello = "Hello from server";
    char _buffer[MAXLINE]; 
    socklen_t len = sizeof(cliaddr);
    // end: define for broadcast

     while(1) {

        // begin: broadcast
        _n = recvfrom(sockfd, (char *)_buffer, MAXLINE, 
                    MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                    &len); 
        _buffer[_n] = '\0'; 
        printf("Client : %s\n", _buffer); 

        sendto(sockfd, (const char *)&_hello, sizeof(_hello), 0, (const struct sockaddr *) &cliaddr, len); 
        // end: broadcast

     }


    return 0;
}
