#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <math.h>
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <stdbool.h>

#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 
int cola;
// #include <process.h>
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 

int stack[MAX];
 
 typedef struct proceso {
int pid;
int burst;
int priority;
struct proceso *anterior;

 }*proceso_ptr;

proceso_ptr front = NULL;
proceso_ptr rear = NULL;

bool is_empty(){

	return (front == NULL);
}

void push(struct proceso p)
{
	//printf("Push: %d, %d, %d", p.pid, p.burst,p.priority);
	proceso_ptr item = (proceso_ptr) malloc(sizeof(struct proceso));
	item->pid=p.pid;
	item->burst=p.burst;
	item->priority=p.priority;
	if(rear == NULL)
		front = rear = item;
	else{
		rear->anterior = item;
		rear = item;
	}
}
 
proceso_ptr pop()
{
	proceso_ptr temp = front;
	front = front->anterior;
	return temp;

}
 
void display(){

	if(is_empty()){

		printf("\nThe queue is empty!\n");
		return;
	}
	proceso_ptr temp = front;
	printf("\n[front -> ");

	while(temp != NULL){
		//printf("- [%d], [%d], [%d] -", temp->pid,temp->burst,temp->priority);
		printf("[%d]", temp->pid);
		temp = temp->anterior;
	}
	printf(" <- rear]\n");

}

void func(int sockfd) 
{ 
	char buff[MAX]; 
	char str;
	char str1[MAX] = " Proceso recibido ";
	int n,read_size; 
	bzero(buff, sizeof(buff)); 

	char cola[]={};

	bzero(buff, sizeof(buff)); 
	
	// infinite loop for chat 
	 for (;;) { 
		bzero(buff, MAX); 
		read(sockfd, buff, sizeof(buff));
	
		puts(buff);
		
		write(sockfd, str1, sizeof(str1)); 
	} 
}


void *job_scheduler(void * sockfd){

	char buff[MAX]; 
	char str;
	int pid=0;
	char respuesta[MAX] = " Proceso recibido. PID: ";
	int n,read_size; 

	char cola[]={};
// 
	bzero(buff, sizeof(buff)); 
	
//	infinite loop for chat 
	 for (;;) {

		char respuesta[MAX] = " Proceso recibido. PID: ";
		bzero(buff, MAX); 
		read(sockfd, buff, sizeof(buff)); 
		char str[MAX];

		printf("servidor recibe:  %s\n", buff);
		char *temp = strtok(buff," ");		
		// if(strlen(buff)==0){
		if(strlen(buff)==0){
			char respuesta1[MAX] = " Finalizado ";		
			write(sockfd, respuesta1, sizeof(respuesta1)); 
			bzero(buff, MAX); 
			pthread_exit();
			close(sockfd); 
		}
		else{
			// char *char_burst = strtok(buff," ");
			char *char_priority = strtok(NULL," ");
			int int_burst=0;
			int int_priority=0;
			// int_burst =	 *char_burst - '0';
			int_burst =	 *temp - '0';
			int_priority = *char_priority - '0';

			//crear pid y enviarlo junto con recibido
			//meterlo en una lista del ready con PCB
			proceso_ptr temp_proccess = (proceso_ptr) malloc(sizeof (struct proceso));
			pid++;
			str[0]= pid+'0';
			strcat(respuesta,str);
			bzero(str, sizeof(str)); 
			write(sockfd, respuesta, sizeof(respuesta)); 
			bzero(respuesta, sizeof(respuesta)); 

			temp_proccess->pid= pid;
			temp_proccess->burst= int_burst;
			temp_proccess->priority= int_priority;
			temp_proccess->anterior= NULL;
			push(*temp_proccess);

		}
		//NO BORRAR : CODIGO DE POP
		// proceso_ptr temp_proccess2 = (proceso_ptr) malloc(sizeof (struct proceso));
		// temp_proccess2= pop();
		// printf("POP: %d", temp_proccess2->pid);	
		 
			// pthread_exit(0);
	} 
}
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

	pthread_t job_scheduler_thread;
	
	pthread_create(&job_scheduler_thread,NULL, job_scheduler,(int *) connfd);
    pthread_join(job_scheduler_thread,NULL);

	display();

	// After chatting close the socket 
	// close(sockfd); 
} 


