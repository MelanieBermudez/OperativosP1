#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <pthread.h>

#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 
//Define para menu consola
#define MAXCHAR 1000
int modo,flag,rangomin,rangomax,tasa;

typedef struct {int*socketfd;char* buffer }SendThread;

void * send_thread(void*args){
	SendThread *actual_args = args;
	printf("\n Actual args: %d \n",actual_args->socketfd);

}
void func(int sockfd, int modo,int rangomin,int rangomax,int tasa) 
{ 
	if(modo==1){
		char buff[MAX]; 
		int n; 
		FILE *fp;
		
		char* filename= "procesos.txt";
		int burst, prioridad;
		int sleep_rand = rand() % (8 + 1-3)+3;

		fp = fopen(filename,"r");
		if (fp==NULL){
			printf("Could not open file %s", filename);
		}
			while(fgets(buff,MAXCHAR,fp)!= NULL){
				printf("buff %s", buff);

			//crear hilo 
			SendThread * args = malloc(sizeof *args);
			args ->socketfd = &sockfd;
			args ->buffer = &buff;
			pthread_t thread_send;
			pthread_create(&thread_send,NULL,send_thread, args);
			pthread_join(thread_send,NULL);

			sleep(2);
			// 	//enviar informacion - esto va dentro de la funcion del hilo  
			
			write(sockfd, buff, sizeof(buff)); 
			bzero(buff, sizeof(buff)); 
				
			read(sockfd, buff, sizeof(buff)); 
			printf("\nFrom Server : %s \n", buff); 
			//pthread_exit(0);
			///
			sleep(sleep_rand);
			}		
			fclose(fp); 
	}else{
		int pid=0;
		int burst;
		int prioridad;
		char buff[MAX]; 
		int n; 

		
		for(;;){
			burst = rand() % (rangomax + 1-rangomin)+rangomin;
			prioridad = rand() % (rangomax + 1-rangomin)+rangomin;
			pid++;
			printf("%PID %d\n",pid);
			printf("%BURST %d\n",burst);
			printf("%PRIORIDAD %d\n",prioridad);
			sleep(2);

			bzero(buff, sizeof(buff)); 
			buff[0]=pid+'0';
			buff[1]=' ';
			buff[2]=burst+'0';
			buff[3]=' ';
			buff[4]=prioridad+'0';
			buff[5]='\0';
			write(sockfd, buff, sizeof(buff)); 
			bzero(buff, sizeof(buff)); 
				
			read(sockfd, buff, sizeof(buff)); 
			printf("\nFrom Server : %s\n", buff); 
			sleep(tasa);
		}
	}

}

char read_file(){
    FILE *fp;
	char str[MAXCHAR];
	char* filename= "procesos.txt";
    int burst, prioridad;

	fp = fopen(filename,"r");
	if (fp==NULL){
		printf("Could not open file %s", filename);
		return 1;
	}
	while(fgets(str,MAXCHAR,fp)!=NULL){
		printf("%s", str);
        //esperar 2 segundos
        sleep(2);
        //enviar informacion    
        //sleep(5)
    }    
	fclose(fp);
	return str;
}



void* myThreadRead(void *arg){
	char buff[MAX]; 
	int n; 
	FILE *fp;
	char* filename= "procesos.txt";
    int burst, prioridad;
	int *sockfd = (int*)arg;

	fp = fopen(filename,"r");
	if (fp==NULL){
		printf("Could not open file %s", filename);
	}	 
	while(fgets(buff,MAXCHAR,fp)!= NULL){
		printf("buff %s", buff);
		sleep(2);

		write(*sockfd, buff, sizeof(buff)); 
		bzero(buff, sizeof(buff)); 
		read(*sockfd, buff, sizeof(buff)); 
		printf("\nFrom Server : %s", buff); 
		sleep(5);
	}
	fclose(fp);    
	return NULL;
}
void* myThreadQueu(void *arg){
	while(1){
	printf("prubea\n");
	scanf("%d", &modo);
	if(modo==1){
		printf("modo   %d",modo);
	}
	sleep(6);
	}
	return NULL;
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
	else{
		printf("connected to the server..\n"); 
	}
	
	printf("---------- Menu de opciones ---------- ");

    printf("\nSeleccione el modo: ");
    printf("\n 1. MANUAL ");
    printf("\n 2. AUTOMATICO \n");

    scanf("%d", &modo);
	if(modo==1){

		pthread_t thread_read;
		pthread_t thread_queu;
		pthread_create(&thread_read,NULL,myThreadRead,(int*) &sockfd);
		// pthread_create(&thread_queu,NULL,myThreadQueu,(int*) &sockfd);
		pthread_join(thread_read,NULL);
		// pthread_join(thread_queu,NULL);

		// return 0;
		
	}
	else{
		//automatico
		printf("\nIndique el rango minimo: ");
		scanf("%d", &rangomin);
		printf("\nIndique el rango maximo: ");
		scanf("%d", &rangomax);
		printf("\nIndique la tasa de creacion de procesos : ");
		scanf("%d", &tasa);

		func(sockfd,modo,rangomin,rangomax,tasa);
		return 0;
	}
	
	// close the socket 
	// close(sockfd); 
} 
