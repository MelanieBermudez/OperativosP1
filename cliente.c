#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netdb.h> 
#include <string.h> 
#include <sys/socket.h> 


//Define para menu consola
#define MAXCHAR 1000
int algoritmo,modo;

//Define para threads
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 

void * myturn(void * arg){

	printf("my turn arg %s",arg);
		
	return NULL;
}

void recibir_msjcli(int n){
    char buff[80];
    read(n,buff,sizeof(buff));
    printf(buff);
    

}

void enviar_msjcli(int n){
    char buff;
    buff = "pueba enviar_msj";
    write(n,buff,sizeof(buff));
    printf(buff);

}

void func(int sockfd) 
{ 
	char buff[MAX]; 
	int n; 
	for (;;) { 
		bzero(buff, sizeof(buff)); 
		printf("Enter the string : "); 
		n = 0; 
		while ((buff[n++] = getchar()) != '\n') 
			; 
		write(sockfd, buff, sizeof(buff)); 
		bzero(buff, sizeof(buff)); 
		read(sockfd, buff, sizeof(buff)); 
		printf("From Server : %s", buff); 
		if ((strncmp(buff, "exit", 4)) == 0) { 
			printf("Client Exit...\n"); 
			break; 
		} 
	} 
} 

int read_file(){
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
		
        //crear hilo
        pthread_t newthread;
	    pthread_create(&newthread,NULL,myturn,str);

        //esperar 2 segundos
        //sleep(2);

        //enviar informacion 
        int res = sockets();
    
        enviar_msjcli(res);
        recibir_msjcli(res);
        

        sleep(5);
        
    }    
	fclose(fp);

	return 0;

    
}

void auto_file(){
    int pid,burst,prioridad;
    

}


int sockets() 
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
    return sockfd;
    

} 

int main(int argc, char*argv[])

{
    printf("---------- Menu de opciones ---------- ");
    printf("\nSeleccione el algoritmo: ");
    printf("\n 1. FIFO ");
    printf("\n 2. SJF ");
    printf("\n 3. HPF ");
    printf("\n 4. ROUND ROBIN \n");

	scanf("%d", &algoritmo);

    printf("\nSeleccione el modo: ");
    printf("\n 1. MANUAL ");
    printf("\n 2. AUTOMATICO \n");

    scanf("%d", &modo);

    if(algoritmo==1){
        //FIFO
        if(modo==1){
            //manual
            read_file();
            return 0;
            
        }
        else{
            //automatico
            auto_file();
            return 0;
        }
    }
    if(algoritmo==2){
        //SJF
        if(modo==1){
            //manual
            read_file();
            return 0;
        }
        else{
            //automatico
            auto_file();
            return 0;
        }
    }
    if(algoritmo==3){
        //HPF
        if(modo==1){
            //manual
            read_file();
            return 0;
        }
        else{
            //automatico
            auto_file();
            return 0;
        }
    }
    else{
        //RR
        if(modo==1){
            //manual
            read_file();
            return 0;
        }
        else{
            //automatico
            auto_file();
            return 0;
        }

    }
    
	

}