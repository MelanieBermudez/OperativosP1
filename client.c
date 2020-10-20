#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 
//Define para menu consola
#define MAXCHAR 1000
int modo,flag;


void func(int sockfd) 
{ 
	char buff[MAX]; 
	int n; 
	FILE *fp;
	
	char* filename= "procesos.txt";
    int burst, prioridad;

	fp = fopen(filename,"r");
	if (fp==NULL){
		printf("Could not open file %s", filename);
	}

	 
		while(fgets(buff,MAXCHAR,fp)!= NULL){
			printf("buff %s", buff);
			// bzero(buff, sizeof(buff)); 
		
		// 	//esperar 2 segundos
		sleep(2);

		// 	//enviar informacion    
		write(sockfd, buff, sizeof(buff)); 
		bzero(buff, sizeof(buff)); 
			
		read(sockfd, buff, sizeof(buff)); 
		printf("\nFrom Server : %s", buff); 

		sleep(5);
}
		fclose(fp);    

	
	
	
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

void auto_file(){
    int pid,burst,prioridad;
	
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
	// function for chat 
	//func(sockfd); 
	printf("---------- Menu de opciones ---------- ");

    printf("\nSeleccione el modo: ");
    printf("\n 1. MANUAL ");
    printf("\n 2. AUTOMATICO \n");

    scanf("%d", &modo);
	if(modo==1){
		//manual
		func(sockfd);
		return 0;
		
	}
	else{
		//automatico
		int rango;
		printf("\nIndique el rango de valores para los procesos : ");
		scanf("%d", &rango);

		auto_file();
		return 0;
	}
	
	// close the socket 
	// close(sockfd); 
} 
