#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 
#define MAXCHAR 1000

void func(int sockfd) 
{ 
	FILE *fp;
	// char str[MAXCHAR];
	char* filename= "procesos.txt";
    int burst, prioridad;

    // int res = sockets();
    // enviar_msjcli(res);
	fp = fopen(filename,"r");
	if (fp==NULL){
		printf("Could not open file %s", filename);
		return 1;
	}
    char buff[MAX];
	while(fgets(buff,MAXCHAR,fp)!=NULL){

	
		for (;;) { 
		bzero(buff, sizeof(buff)); 
		// printf("Enter the string : "); 
		printf("leido    ",buff);
        
		write(sockfd, buff, sizeof(buff)); 
		// bzero(buff, sizeof(buff)); 

		read(sockfd, buff, sizeof(buff)); 

		printf("From Server : %s", buff); 

	}
        

        sleep(5);
        
    }    

	fclose(fp);

	
} 

int main() 
{ 
	int sockfd, connfd; 
	struct sockaddr_in servaddr, cli; 

	// socket create and varification 
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
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(PORT); 

	// connect the client socket to server socket 
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
		printf("connection with the server failed...\n"); 
		exit(0); 
	} 
	else
		printf("connected to the server..\n"); 

	// function for chat 
	func(sockfd); 

    

	// close the socket 
	// close(sockfd); 
} 
