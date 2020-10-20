#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 

void func(int sockfd) 
{ 
	char buff[MAX]; 
	
	bzero(buff, sizeof(buff)); 

	// infinite loop for chat 
	 for (;;) { 
		bzero(buff, MAX); 
		read(sockfd, buff, sizeof(buff)); 
		puts(buff);
		// printf("From client: %s\t To client : ", buff); 
		char s[]="recibido\n";
		
		//hay que meterlo a la cola hilo
		//un hilo haga lo de la cola
		//y el otro lo del socket
		

		write(sockfd, s, sizeof(s)); 
		

	} 
} 


// void func(int sockfd) 
// { 
// 	char buff[MAX]; 
// 	int n; 

// 	bzero(buff, sizeof(buff)); 
// 	printf("Enter the string : "); 
// 	n = 0; 
// 	while ((buff[n++] = getchar()) != '\n') 
// 		; 
// 	write(sockfd, buff, sizeof(buff)); 
// 	bzero(buff, sizeof(buff)); 
// 	read(sockfd, buff, sizeof(buff)); 
// 	printf("From Server : %s", buff); 

	
// } 

// Driver function 
int main() 
{ 
	int sockfd, connfd, len; 
	struct sockaddr_in servaddr, cli; 

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("socket bind failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded..\n"); 

	// Now server is ready to listen and verification 
	if ((listen(sockfd, 5)) != 0) { 
		printf("Listen failed...\n"); 
		exit(0); 
	} 
	else
		printf("Server listening..\n"); 
	len = sizeof(cli); 

	// Accept the data packet from client and verification 
	connfd = accept(sockfd, (SA*)&cli, &len); 
	if (connfd < 0) { 
		printf("server acccept failed...\n"); 
		exit(0); 
	} 
	else
		printf("server acccept the client...\n"); 

	// Function for chatting between client and server 
	func(connfd); 
    

	// After chatting close the socket 
	// close(sockfd); 
} 


