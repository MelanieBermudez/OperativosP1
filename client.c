#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <pthread.h>
#include <sys/types.h>

#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 
//Define para menu consola

int modo,flag,rangomin,rangomax,tasa;
int cancel=1;

typedef struct {
int *socketfd;
char *buffer;
char *msg[MAX];
 }SendThread;

void* verificar_cola(){
	int opt;
	for(;;){
		scanf("%d", &opt);
		if(opt==0){
			exit(0);
			printf("es 0");
			pthread_exit(0);
			cancel=0;
		}
	}
}
 			
void *send_thread(void *args){

	SendThread *actual_args = args;
	char buff[MAX] = "PROCESO ENVIADO";
	// free(actual_args);
	int socckfd= *actual_args->socketfd;
	char *str1 = actual_args->buffer;
	sleep(2);
	printf("\nto Server : %s \n", str1); 
	write(socckfd, str1, sizeof(str1)); 
	bzero(buff, sizeof( buff)); 				
	read( socckfd,  buff, sizeof(buff)); 
	printf("\nFrom Server : %s \n", buff); 
	pthread_exit(0);	
}

void func(int sockfd, int modo,int rangomin,int rangomax,int tasa) 
{ 
	int sleep_rand = rand() % (8 + 1-3)+3;
	if(modo==1) {
		char buff[MAX]; 
		char buffa[MAX] = "PROCESO ENVIADO";
		int n; 
		FILE *fp;
		char* filename= "procesos.txt";
		int burst, prioridad;
		fp = fopen(filename,"r");
		if (fp==NULL){
			printf("Could not open file %s", filename);
		}
			while(fgets(buff,MAX,fp)!= NULL){
			SendThread * args = malloc(sizeof *args);
			args ->socketfd = &sockfd;
			args ->buffer = &buff;
			pthread_t thread_send;
			pthread_create(&thread_send,NULL,send_thread, args);
			sleep(sleep_rand);
			pthread_join(thread_send,NULL);
			int pthread_cancel(pthread_t thread_send);
			
			}		
			fclose(fp); 
	}
	else{
		int burst;
		int prioridad;
		char buff[MAX]; 
		char buffa[MAX] = "PROCESO ENVIADO";
		int n=0;

		while(cancel!=0){

			burst = rand() % (rangomax + 1-rangomin) + rangomin;
			prioridad = rand() % (rangomax + 1-rangomin)+rangomin;
			bzero(buff, sizeof(buff)); 
			buff[0]=burst+'0';
			buff[1]=' ';
			buff[2]=prioridad+'0';
			buff[3]='\0';
			printf("buff%s",buff);
			SendThread * args = malloc(sizeof *args);
			args ->socketfd = &sockfd;
			args ->buffer = &buff;
			pthread_t thread_send;
			pthread_create(&thread_send,NULL,send_thread, args);
			sleep(sleep_rand);
			pthread_join(thread_send,NULL);
			int pthread_cancel(pthread_t thread_send);
			n++;
			printf("\ncantidad de procesos %d:\n ", n);
		}
		pthread_exit(0);
	}
}


int main() 
{ 
	srand (5);
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
	else{
		printf("connected to the server..\n"); 
	}
	
	printf("---------- Menu de opciones ---------- ");
    printf("\nSeleccione el modo: ");
    printf("\n 1. MANUAL ");
    printf("\n 2. AUTOMATICO \n");

    scanf("%d", &modo);
	if(modo==1){
		func(sockfd,modo,0,0,0);
	}
	else{
		//automatico
		printf("\nIndique el rango minimo: ");
		scanf("%d", &rangomin);
		printf("\nIndique el rango maximo: ");
		scanf("%d", &rangomax);
		printf("\nIndique la tasa de creacion de procesos : ");
		scanf("%d", &tasa);
		printf("\n Para terminar de ejecutar presione: 0 \n");

		pthread_t cola_thread;
		pthread_create(&cola_thread,NULL,verificar_cola ,NULL);

		func(sockfd,modo,rangomin,rangomax,tasa);
		pthread_join(cola_thread,NULL);
		return 0;
	}
	// close the socket 
	// close(sockfd); 
}