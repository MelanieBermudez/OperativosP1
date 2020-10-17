#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

//prueba readfile
#define MAXCHAR 1000

//esto es una prueba de cpu scheduling 
#define BIG 10000000L
#define DIVIDER 500

void do_busy_things(int niceval){
	nice(niceval);
	for (long i=0;i<BIG;i++){
		if(i%(BIG/DIVIDER)==0){
			printf("p=%d ---> %ld\n",niceval,i);
		}
	}

}


//esto es la prueba de pthreads
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
	//Prueba threads 
	// pthread_t newthread;
	// pthread_create(&newthread,NULL,myturn,NULL);

	// yourturn();

	// //waits until a thread finishes to execute 
	// pthread_join(&newthread,NULL);

	//Prueba cpu scheduler con fork 
	if(fork()==0){
		do_busy_things(1);
	}else{
		do_busy_things(2);
	}

	//Prueba readfile
	FILE *fp;
	char str[MAXCHAR];
	char* filename= "procesos.txt";

	fp = fopen(filename,"r");
	if (fp==NULL){
		printf("Could not open file %s", filename);
		return 1;
	}
	while(fgets(str,MAXCHAR,fp)!=NULL)
		printf("%s",str);
	fclose(fp);

	return 0;
}
