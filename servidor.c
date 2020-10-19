#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netdb.h> 
#include <string.h> 
#include <sys/socket.h> 
#define MAXCHAR 1000
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 



void * job_scheduler_info(void * arg){

	printf("job scheduler info: %s ",arg);
		
	return NULL;
}

void * cpu_scheduler_info(void * arg){

	printf("cpu scheduler info: %s ",arg);
		
	return NULL;
}

void recibir_msj(int n){
	printf("recibir mensaje")
    char buff[80];
    read(n,buff,sizeof(buff));
    printf(buff);
    

}

void enviar_msj(int n){
    char buff;
    buff = "pueba enviar_msj";
    write(n,buff,sizeof(buff));
    printf(buff);

}
void func(int sockfd) 
{ 
	char buff[MAX]; 
	int n; 

	bzero(buff, sizeof(buff)); 
	printf("Enter the string : "); 
	n = 0; 
	while ((buff[n++] = getchar()) != '\n') 
		; 
	write(sockfd, buff, sizeof(buff)); 
	bzero(buff, sizeof(buff)); 
	read(sockfd, buff, sizeof(buff)); 
	printf("From Server : %s", buff); 

	
} 

void conectar() 
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
	else{
		printf("server acccept the client...\n"); 

    }

	func(sockfd);

    // return sockfd;    
} 

int main (int argc, char*argv[]){

    //aqui va a llegar un msj 

    //recibimos el mensaje con job_sched y lo metemos a la cola []


    //job scheduler 
    // pthread_t job_sched;
    // pthread_create(&job_sched,NULL,job_scheduler_info,"msj");

    // //read socket

    // //cpu scheduler 
    // pthread_t cpu_sched;
    // pthread_create(&cpu_sched,NULL,cpu_scheduler_info,"msj2");

    // pthread_join(&job_sched,NULL);

    // printf("\n");

	conectar();

    // recibir_msj(res);


   	// enviar_msj(res);
	int a =4312313;



}
