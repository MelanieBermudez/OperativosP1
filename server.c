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
	int pid=1;
	char str1[MAX] = " Proceso recibido ";
	int n,read_size; 

	printf("socckd %d ",sockfd);
	char cola[]={};
// 
	bzero(buff, sizeof(buff)); 
	
//	infinite loop for chat 
	 for (;;) { 
		bzero(buff, MAX); 
		read(sockfd, buff, sizeof(buff)); 
		if(buff != NULL){
		printf("\nBuffer: %s\n",buff);
		}
		char str[MAX];
		//crear pid y enviarlo junto con recibido
		//meterlo en una lista del ready con PCB
		printf("pid%d",pid);
		pid++;
		// itoa(pid,str,10);
		sprintf(str, "%d", pid);
		printf("str:  %s",str);
		write(sockfd, str1, sizeof(str1)); 
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
	
	printf("asdsdas %d ",&connfd);

	pthread_t job_scheduler_thread;
	
	pthread_create(&job_scheduler_thread,NULL, job_scheduler,(int *) connfd);
    pthread_join(job_scheduler_thread,NULL);




	// After chatting close the socket 
	// close(sockfd); 
} 


