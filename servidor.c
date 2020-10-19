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
int algoritmo;



void * job_scheduler_info(void * arg){

	printf("job scheduler info: %s ",arg);
		
	return NULL;
}

void * cpu_scheduler_info(void * arg){

	printf("cpu scheduler info: %s ",arg);
		
	return NULL;
}

void recibir_msj(int n){
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
        recibir_msj(sockfd);
    }
    //return sockfd;    
} 

int main (int argc, char*argv[]){
	printf("---------- Menu de opciones ---------- ");
    printf("\nSeleccione el algoritmo: ");
    printf("\n 1. FIFO ");
    printf("\n 2. SJF ");
    printf("\n 3. HPF ");
    printf("\n 4. ROUND ROBIN \n");
	printf("\n 5. Salir \n");
	
	scanf("%d", &algoritmo);
	switch(algoritmo){
			case 1:
				//FCFS(P,n);
				break;
			case 2:
				//SJF_P(P,n);
				break;
			case 3:
				//SJF_NP(P,n);
				break;
			case 4:
				//PRT_P(P,n);
				break;
			case 5: exit(0);
		}




    // //job scheduler 
    // pthread_t job_sched;
    // pthread_create(&job_sched,NULL,job_scheduler_info,"msj");

    // //read socket

    // //cpu scheduler 
    // pthread_t cpu_sched;
    // pthread_create(&cpu_sched,NULL,cpu_scheduler_info,"msj2");

    // pthread_join(&job_sched,NULL);

    // printf("\n");

    // conectar();



}
