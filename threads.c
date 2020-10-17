#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

void * myturn(void * arg){
	while(1){
		sleep(1);
		printf("My turn \n");
	}
	return NULL;
}
void yourturn(){
	while(1){
		sleep(2);
		printf("your turn \n");
	}
}
int main(int argc, char*argv[])
{
	pthread_t newthread;
	pthread_create(&newthread,NULL,myturn,NULL);
	
	//myturn();
	yourturn();
	return 0;
}
