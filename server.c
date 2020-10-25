#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <math.h>
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 

#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 
int cola;
// #include <process.h>
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 
 
int top=-1;
int stack[MAX];
void push(int *val);
void pop();
void display();
 
 typedef struct {
int *pid;
int *burst;
int *priority;

 }Proceso;


void push(int *val)
{	
	// printf("el valor a insertar es: ");;
	// printf(&val);
	// printf(*val);
	printf("vlar %s ",&val);
	top=top+1;
	stack[top]=&val;

}
 
void pop()
{
	if(top==-1)
	{
		printf("\nStack is empty!!");
	}
	else
	{
		printf("\nDeleted element is %d",stack[top]);
		top=top-1;
	}
}
 
void display()
{
	int i;
	if(top==-1){
		printf("\nStack is empty!!");
	}
	else{
		printf("\nStack is...\n");
		for(i=top;i>=0;--i)
			printf("%d\n",stack[i]);
	}
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




		//crear pid y enviarlo junto con recibido
		//meterlo en una lista del ready con PCB


	// // push(buff);
	// 	top=top+1;
	// 	stack[top]=&buff;
	// 	display();

		
		write(sockfd, str1, sizeof(str1)); 
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
	 for (int i=0; i<=4;i++) {

		char respuesta[MAX] = " Proceso recibido. PID: ";
		bzero(buff, MAX); 
		read(sockfd, buff, sizeof(buff)); 
		char str[MAX];

		printf("budd %s\n", buff);
		char *temp = strtok(buff," ");		
		// if(strlen(buff)==0){

		printf("te,p %s\n", temp);
		if(*temp == '0'){
			char respuesta1[MAX] = " Finalizado ";		
			printf("%s",respuesta);
			write(sockfd, respuesta1, sizeof(respuesta1)); 
			close(sockfd); 
		}
		else{
			printf("adneto %s\n", buff);
			// char *char_burst = strtok(buff," ");
			char *char_priority = strtok(NULL," ");
			int int_burst=0;
			int int_priority=0;
			// int_burst =	 *char_burst - '0';
			int_burst =	 *temp - '0';
			int_priority = *char_priority - '0';

			//crear pid y enviarlo junto con recibido
			//meterlo en una lista del ready con PCB
			Proceso *temp_proccess = malloc(sizeof * temp_proccess);

			pid++;
			str[0]= pid+'0';
			strcat(respuesta,str);
			bzero(str, sizeof(str)); 
			write(sockfd, respuesta, sizeof(respuesta)); 
			bzero(respuesta, sizeof(respuesta)); 


			temp_proccess->pid= &pid;
			temp_proccess->burst= &int_burst;
			temp_proccess->priority= &int_priority;

			printf("ID %d\n",*temp_proccess->pid);
			// printf("BURST %d\n",*temp_proccess->burst);
			// printf("priority %d\n",*temp_proccess->priority);
	
		// else{
		}
		 
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

	// Function for chatting between client and server 
	// func(connfd); 
	

	pthread_t job_scheduler_thread;
	
	pthread_create(&job_scheduler_thread,NULL, job_scheduler,(int *) connfd);
    pthread_join(job_scheduler_thread,NULL);




	// After chatting close the socket 
	// close(sockfd); 
} 


