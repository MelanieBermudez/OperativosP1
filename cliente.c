#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


#define MAXCHAR 1000
int algoritmo,modo;

void read_file(){
	FILE *fp;
	char str[MAXCHAR];
	char* filename= "procesos.txt";

	fp = fopen(filename,"r");
	if (fp==NULL){
		printf("Could not open file %s", filename);
		
	}
    //aqui hacemos el sleep y el hilo...
	while(fgets(str,MAXCHAR,fp)!=NULL)
		printf("%s",str);
	fclose(fp);
    
}

void auto_file(){
    int pid,burst,prioridad;
    

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
            
        }
        else{
            //automatico
            auto_file();
        }
    }
    if(algoritmo==2){
        //SJF
        if(modo==1){
            //manual
            read_file();
        }
        else{
            //automatico
            auto_file();
        }
    }
    if(algoritmo==3){
        //HPF
        if(modo==1){
            //manual
            read_file();
        }
        else{
            //automatico
            auto_file();
        }
    }
    else{
        //RR
        if(modo==1){
            //manual
            read_file();
        }
        else{
            //automatico
            auto_file();
        }
    }
    
	

}