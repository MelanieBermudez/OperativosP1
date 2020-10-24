// #include <netdb.h> 
// #include <stdlib.h> 
// #include <string.h> 
// #include <sys/socket.h> 
#include <pthread.h>
#include <unistd.h>
#include <stdio.h> 

#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 
//Define para menu consola
#define MAXCHAR 1000
int modo,flag;

void* myThreadRead(void *arg){
	// // int *connfd = (int *)args;
	// printf("peyebas");
	// for (int i=0; i<4; i++){
	// 	printf("hola");
	// }
	// // printf("prueba%d ",connfd


        while(1){
            sleep(2);
            printf("thread\n");
    }

	return NULL;
}

void readT(){
    while(1){
        sleep(2);
        printf("read\n");
    }

}

int main() 
{ 

	pthread_t thread_read;
	pthread_create(&thread_read,NULL,myThreadRead,NULL);
    readT();
	// pthread_join(&thread_read,NULL);

	// close the socket 
	// close(sockfd); 
} 
