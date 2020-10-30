#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <math.h>
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <stdbool.h>
#include <time.h>

#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 

int cantidad_procesos_realizados, cpu_ocioso;
int algoritmo;
int quantum = 0; 
int procesos_cola;
int cant_procesos=0;

// int sumw=0,sumt=0;
// int wt=0;
// int x = 0;

int sumw=0,sumt=0;
int wt=0;
int x = 0;

float avgwt=0.0,avgta=0.0;
int opcion=1;
 
typedef struct proceso {
	int pid;
	int burst;
	int priority;
	bool estado;
	int ejecutado;
	int wt,ta;
	struct proceso *anterior;

 }*proceso_ptr;

proceso_ptr front = NULL;
proceso_ptr rear = NULL;

proceso_ptr proc_ejecutados_front = NULL;
proceso_ptr proc_ejecutados_rear = NULL;

bool is_empty(){

	return (front == NULL);
}
bool is_empty_ejec(){

	return (proc_ejecutados_front == NULL);
}

void display(){
	if(is_empty()){
		printf("\nCola Ready Vacia\n");
		return;
	}
	proceso_ptr temp = front;
	printf("\n Cola Ready \n Procesos:  ");
	while(temp != NULL){
		printf("\033[0;31m");
		printf("[%d]", temp->pid);
		printf("\033[0m;");
		temp = temp->anterior;
	}
	printf("\n");
}
void display_ejecutados(){
	if(is_empty_ejec()){
		printf("\nCola ejecutados vacia!\n");
		return;
	}
	proceso_ptr temp = proc_ejecutados_front;
	printf("\nCola ejecutado\n Procesos: ");
	while(temp != NULL){
		//printf("- [%d], [%d], [%d] -", temp->pid,temp->burst,temp->priority);
		printf("[%d]", temp->pid);
		temp = temp->anterior;
	}
	printf("\n");
}
void push(struct proceso p)
{
	//printf("Push: %d, %d, %d", p.pid, p.burst,p.priority);
	proceso_ptr item = (proceso_ptr) malloc(sizeof(struct proceso));
	item->pid=p.pid;
	item->burst=p.burst;
	item->priority=p.priority;
	item->ejecutado=p.ejecutado;
	item->estado=p.estado;
	item->ta=p.ta;
	item->wt=p.wt;
	//item->anterior=NULL;
	if(rear == NULL)
		front = rear = item;
	else{
		rear->anterior = item;
		rear = item;
	}
}
void push_ejecutados(struct proceso p)
{
	//printf("Push: %d, %d, %d", p.pid, p.burst,p.priority);
	proceso_ptr item = (proceso_ptr) malloc(sizeof(struct proceso));
	item->pid=p.pid;
	item->burst=p.burst;
	item->priority=p.priority;
	item->ejecutado=p.ejecutado;
	item->estado=p.estado;
	item->ta=p.ta;
	item->wt=p.wt;
	//item->anterior=NULL;
	if(proc_ejecutados_rear == NULL)
		proc_ejecutados_front = proc_ejecutados_rear = item;
	else{
		proc_ejecutados_rear->anterior = item;
		proc_ejecutados_rear = item;
	}
}
void push_hpf(struct proceso p){
	
	proceso_ptr item = (proceso_ptr) malloc(sizeof(struct proceso));
	item->pid=p.pid;
	item->burst=p.burst;
	item->priority=p.priority;
	item->ejecutado=p.ejecutado;
	item->estado=p.estado;
	item->ta=p.ta;
	item->wt=p.wt;
	if(front == NULL){
		front = rear = item;
	}
	else
	{
		if(item->priority < front->priority){
			item->anterior=front;
			front=item;
		}
		else
		{
			proceso_ptr temp= front;
			proceso_ptr atras= front;
			while(item->priority > temp->priority && temp->anterior !=NULL){
				atras=temp;
				temp=temp->anterior; 
			}
			if(item->priority > temp->priority){
				temp->anterior=item;
			}
			else{
				item->anterior=temp;
				atras->anterior= item;
			}
			
		}
	}
}
	
void push_sjf(struct proceso p){

	proceso_ptr item = (proceso_ptr) malloc(sizeof(struct proceso));
	item->pid=p.pid;
	item->burst=p.burst;
	item->priority=p.priority;
	item->ejecutado=p.ejecutado;
	item->estado=p.estado;
	item->ta=p.ta;
	item->wt=p.wt;
	if(front == NULL){
		front = rear = item;
	}
	else
	{
		if(item->burst < front->burst){
			item->anterior=front;
			front=item;
		}
		else
		{
			proceso_ptr temp= front;
			proceso_ptr atras= front;
			while(item->burst > temp->burst && temp->anterior !=NULL){
				atras=temp;
				temp=temp->anterior; 
			}
			if(item->burst > temp->burst){
				temp->anterior=item;
			}
			else{
				item->anterior=temp;
				atras->anterior= item;
			}
			
		}
	}
}
void push_rr(struct proceso p){}

proceso_ptr pop()
{
	proceso_ptr temp = front;
	front = front->anterior;
	return temp;

}
proceso_ptr pop_index(int index)
{	

	int size= cola_size();
	int cont=1;
	
	proceso_ptr temp = front;
	
	while(temp->anterior!=NULL)
	{

		if(temp->pid != index){
			push(*temp);
		}
		temp= temp->anterior;
	}

	return temp;

}

 


int cola_size(){
	int n =0;
	if(is_empty()){
		printf("\nTCola vacia\n");
		return 0;
	}
	proceso_ptr temp = front;
	while(temp != NULL){
		n++;
		temp = temp->anterior;
	}
	return n;
}

void RR(){
	int cant_cola = cola_size();
	int n = 0;

	
	n = procesos_cola;
	proceso_ptr temp = front;
	sleep(5);
	int sumw=0,sumt=0;
	int wt=0;
	int x = 0;
	if(cant_cola!=0){
		while(temp->anterior != NULL){
			if(temp->ejecutado <= quantum){
				temp->wt = wt; //ta del temp-1 o la suma de ejecutado que ya se ejecutaron
				temp->ta = temp->wt+temp->ejecutado;
				sumw+= wt;
				sumt+=temp->ta;
				wt+= temp->ejecutado;
				printf("\nEjecutando proceso: %d Burst: %d Prioridad: %d \n", temp->pid ,temp->ejecutado, temp->priority );
				sleep(temp->ejecutado);
				proceso_ptr temp_proccess2 = (proceso_ptr) malloc(sizeof (struct proceso));
				temp_proccess2= pop();
				temp_proccess2->estado= true;
				push_ejecutados(*temp);
			}else{
					
				int resta= temp->ejecutado- quantum;
				printf("resta%d",resta);
				temp->wt = wt; 
				temp->ta = temp->wt+quantum;
				sumw+= wt;
				sumt+=temp->ta;
				wt+= quantum;
				printf("\nEjecutando proceso %d con quatum  %d\n", temp->pid, quantum);
				sleep(quantum);
				temp->ejecutado= resta;
				proceso_ptr temp_proccess2 = (proceso_ptr) malloc(sizeof (struct proceso));
				temp_proccess2= pop();
				temp_proccess2->estado= false;
				push(*temp);
			}		
			temp = temp->anterior;			
		}
		while(temp->ejecutado > 0){

			if( temp->ejecutado >= quantum){
				int resta= temp->ejecutado- quantum;
				temp->wt = wt; 
				temp->ta =  temp->wt + quantum;
				cant_cola--;
				temp->ejecutado= resta;
			}else{
				int resta= temp->ejecutado- quantum;
				temp->wt = wt; //ta del temp-1 o la suma de los ejecutado que ya se ejecutaron
				temp->ta = temp->wt+temp->ejecutado;
				sumw+= wt;
				sumt+=temp->ta;
				wt+= temp->ejecutado;
				temp->ejecutado= 0;

				proceso_ptr temp_proccess2 = (proceso_ptr) malloc(sizeof (struct proceso));
				temp_proccess2= pop();
				sleep(4);
				temp_proccess2->estado= true;
				push_ejecutados(*temp);
			}
		}
		proceso_ptr temp1 = proc_ejecutados_front;
		printf("\n\n PROC.\tB.T.\tW.T\tT.A.T");
		while(temp1->anterior != NULL){
			printf("\n %d\t%d\t%d\t%d",temp1->pid,temp1->burst,temp1->wt,temp1->ta);
			temp1 = temp1->anterior;
		}
		printf("\n %d\t%d\t%d\t%d",temp1->pid,temp1->burst,temp1->wt,temp1->ta);
	}
}

void SJF(){
	// int sumw=0;
	// int sumt=0;
	int wt=0;
	// int x = 0;
	// float avgwt=0.0,avgta=0.0;
	int cant_cola = cola_size();
	int n = 0;
	n = procesos_cola;
	proceso_ptr temp = front;
	sleep(5);
	if(cant_cola!=0){
		//for(i=1;i<n;i++){
			while(temp != NULL){

				// printf("este es el burst %d\n",temp->burst );
				temp->wt = wt; //ta del temp-1 o la suma de los burst que ya se ejecutaron
				temp->ta = temp->wt + temp->burst;
				// printf("este es el ta %d\n",temp->ta );
				sumw+= wt;
				sumt+=temp->ta;
				wt+= temp->burst;

				proceso_ptr temp_proccess2 = (proceso_ptr) malloc(sizeof (struct proceso));
				temp_proccess2= pop();
				push_ejecutados(*temp_proccess2);
				printf("\n\ntemp->wt %d\n",temp->wt);
				printf("temp->ta %d\n",temp->ta );
				printf("sumw%d\n",sumw);
				printf("sumt%d\n",sumt);
				printf("wt%d\n",wt);
				display();
				printf("\nEjecutando proceso: %d Burst: %d Prioridad: %d \n", temp->pid ,temp->burst, temp->priority );
				// sleep(temp->burst);
				temp = temp->anterior;
			}


		// display_ejecutados();
		printf("\n\n PROC.\tB.T.\tW.T\tT.A.T");
		proceso_ptr temp1 = proc_ejecutados_front;
		while(temp1->anterior != NULL){
			printf("\n %d\t%d\t%d\t%d",temp1->pid,temp1->burst,temp1->wt,temp1->ta);
			temp1 = temp1->anterior;
		}
		printf("\n %d\t%d\t%d\t%d",temp1->pid,temp1->burst,temp1->wt,temp1->ta);
	}
}
void HPF(){
	int wt=0;
	int cant_cola = cola_size();
	int n = 0;
	n = procesos_cola;
	proceso_ptr temp = front;
	sleep(5);
	if(cant_cola!=0){
			while(temp != NULL){
				temp->wt = wt; //ta del temp-1 o la suma de los burst que ya se ejecutaron
				temp->ta = temp->wt + temp->burst;
				sumw+= wt;
				sumt+=temp->ta;
				wt+= temp->burst;
				printf("\nEjecutando proceso: %d Burst: %d Prioridad: %d \n", temp->pid ,temp->burst, temp->priority );

				display();
				proceso_ptr temp_proccess2 = (proceso_ptr) malloc(sizeof (struct proceso));
				temp_proccess2= pop();
				push_ejecutados(*temp_proccess2);
				sleep(temp->burst);
				temp = temp->anterior;
			}


		// display_ejecutados();
		printf("\n\n PROC.\tB.T.\tW.T\tT.A.T");
		proceso_ptr temp1 = proc_ejecutados_front;
		while(temp1->anterior != NULL){
			printf("\n %d\t%d\t%d\t%d",temp1->pid,temp1->burst,temp1->wt,temp1->ta);
			temp1 = temp1->anterior;
		}
		printf("\n %d\t%d\t%d\t%d",temp1->pid,temp1->burst,temp1->wt,temp1->ta);
	}
}



void FCFS(){
	int sumw=0,sumt=0;
	int wt=0;
	int x = 0;
	float avgwt=0.0,avgta=0.0;
	int cant_cola = cola_size();
	int n = 0;
	n = procesos_cola;
	proceso_ptr temp = front;
	sleep(15);
	if(cant_cola!=0){
			while(temp->anterior != NULL){
				temp->wt = wt; //ta del temp-1 o la suma de los burst que ya se ejecutaron
				temp->ta = temp->wt+temp->burst;
				sumw+= wt;
				sumt+=temp->ta;
				wt+= temp->burst;
				printf("\nEjecutando proceso: %d Burst: %d Prioridad: %d \n", temp->pid ,temp->burst, temp->priority );
				sleep(temp->burst);
				temp = temp->anterior;

				proceso_ptr temp_proccess2 = (proceso_ptr) malloc(sizeof (struct proceso));
				temp_proccess2= pop();
				// printf("------------------------------------------------ \n" );
				printf("Proceso ejecutado terminado:  %d\n", temp_proccess2->pid);
				push_ejecutados(*temp_proccess2);
			}
		// printf("------------------------------------------------ \n" );
		printf("\nEjecutando proceso: %d Burst: %d Prioridad: %d \n", temp->pid ,temp->burst, temp->priority );
		sleep(temp->burst);
		//proc_ejecutados_front->anterior;
		temp->wt = wt; //(temp->anterior->ta); //ta del temp-1 o la sumw de los burst que ya se ejecutaron
		temp->ta =  temp->wt +  temp->burst;
		// sumt+=temp->ta;
		cant_cola--;

		proceso_ptr temp_proccess2 = (proceso_ptr) malloc(sizeof (struct proceso));
		temp_proccess2= pop();
		printf("Proceso ejecutado terminado: %d \n", temp_proccess2->pid);
		push_ejecutados(*temp_proccess2);

		avgwt = (float)sumw/cant_procesos;
		avgta = (float)sumt/cant_procesos;
		// display_ejecutados();
		printf("\n\n PROC.\tB.T.\tW.T\tT.A.T");
		proceso_ptr temp1 = proc_ejecutados_front;
		while(temp1->anterior != NULL){
			printf("\n %d\t%d\t%d\t%d",temp1->pid,temp1->burst,temp1->wt,temp1->ta);
			temp1 = temp1->anterior;
		}
		printf("\n %d\t%d\t%d\t%d",temp1->pid,temp1->burst,temp1->wt,temp1->ta);
		// printf("\n\n Average waiting time = %0.2f - Average turn-around = %0.2f.",avgwt,avgta);
	}
}

void *job_scheduler(void * sockfd){
	char buff[MAX]; 
	char str;
	int pid=0;
	char respuesta[MAX] = " Proceso recibido. PID: ";
	int n,read_size; 
	char cola[]={};
	bzero(buff, sizeof(buff)); 
	 for (;;) {
		char respuesta[MAX] = " Proceso recibido. PID: ";
		bzero(buff, MAX); 
		read(sockfd, buff, sizeof(buff)); 
		char str[MAX];
		printf("\nRecibiendo proceso:  %s\n", buff);
		char *temp = strtok(buff," ");		
		if(strlen(buff)==0){
			char respuesta1[MAX] = " Finalizado ";		
			write(sockfd, respuesta1, sizeof(respuesta1)); 
			bzero(buff, MAX); 
			pthread_exit();
			close(sockfd); 
		}
		else{
		if(opcion !=0){
			char *char_priority = strtok(NULL," ");
			int int_burst=0;
			int int_priority=0;
			int_burst =	 *temp - '0';
			int_priority = *char_priority - '0';
			proceso_ptr temp_proccess = (proceso_ptr) malloc(sizeof (struct proceso));
			pid++;
			str[0]= pid+'0';
			strcat(respuesta,str);
			bzero(str, sizeof(str)); 
			write(sockfd, respuesta, sizeof(respuesta)); 
			bzero(respuesta, sizeof(respuesta)); 
			temp_proccess->pid= pid;
			temp_proccess->burst= int_burst;
			temp_proccess->priority= int_priority;
			temp_proccess->anterior= NULL;
			temp_proccess->estado=false;
			temp_proccess->ejecutado=int_burst;
			procesos_cola++;
			cant_procesos++;

			if(algoritmo==1){
				push(*temp_proccess);
			}
			else if(algoritmo==2){
				push_hpf(*temp_proccess);
			}
			else if(algoritmo==3){
				push_sjf(*temp_proccess);
			}
			else if(algoritmo ==4){
				push(*temp_proccess);
			}

		}
		}
		// display();
		//NO BORRAR : CODIGO DE POP
			// pthread_exit(0);
	} 
}

void *cpu_scheduler(void *algoritmo){
	
	int n; 
	for(;;){
		if (algoritmo ==1){
			if(is_empty()){
				int a =1;
			}else{
				FCFS();

			}
		}
		else if (algoritmo ==2){
			if(is_empty()){
				int a =1;
			}else{
				// sleep(10);

				HPF();
			}
		}
		else if (algoritmo ==3){
			if(is_empty()){
				int a =1;
			}else{
				sleep(10);
				SJF();
			}
		}
		else if (algoritmo ==4){


			if(is_empty()){
				int a =1;
			}else{
				
				sleep(30);
				RR();
			}



		}
	}
	
}

void calcular_avg(){
	int avg_wt=0;
	int avg_ta=0;  
	int cont = 0;
	proceso_ptr temp = proc_ejecutados_front;
	while(temp != NULL){
		avg_wt += temp->wt;
		avg_ta += temp->ta;
		temp = temp->anterior;
		cont++;
	}
	printf("Procesos totales:%d \n",cont);
	printf("Promedio WT: %f\n",(float) avg_wt/cont);
	printf("Promedio TA: %f \n", (float)avg_ta/cont);
	printf("\n");
}

void display_todo(){
	calcular_avg();
	
	display();
	display_ejecutados();

		
	printf("\n\n PROC.\tB.T.\tW.T\tT.A.T\tPrioridad");
	proceso_ptr temp1 = proc_ejecutados_front;
	while(temp1 != NULL){
		printf("\n %d\t%d\t%d\t%d\t%d" ,temp1->pid,temp1->burst,temp1->wt,temp1->ta,temp1->priority);
		temp1 = temp1->anterior;
	}

	printf("\n");

}
void* verificar_cola(){
	int n;
	for(;;){
		scanf("%d", &n);
		if(n==5){
			display();
		}
		else if(n==6){
			display_ejecutados();
		}
		else if(n==7){
			display_todo();
			//close(sockfd); 
			exit(0);
			// opcion=0;
			// pthread_exit(0);
			// // break;
		}
	}
}

int main() 
{ 
	int sockfd, connfd, len; 
	struct sockaddr_in servaddr, cli; 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 

	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("socket bind failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded..\n"); 

	if ((listen(sockfd, 5)) != 0) { 
		printf("Listen failed...\n"); 
		exit(0); 
	} 
	else
		printf("Server listening..\n"); 
	len = sizeof(cli); 

	connfd = accept(sockfd, (SA*)&cli, &len); 
	if (connfd < 0) { 
		printf("server acccept failed...\n"); 
		exit(0); 
	} 
	else
		printf("server acccept the client...\n"); 
	
	printf("---------- Menu de opciones ---------- ");
    printf("\n 1. FIFO ");
    printf("\n 2. HPF ");
    printf("\n 3. SJF ");
    printf("\n 4. ROUND ROBIN");
	printf("\n 5. Verificar la cola del ready\n");
	printf("\n 6. Verificar la cola de procesados\n");
	printf("\n 7. Terminar la ejecucion\n");
	
	scanf("%d", &algoritmo);

	if(algoritmo==4){
		printf("Round Robin");
		printf("\nIngrese el quantum: ");
		scanf("%d", &quantum);
	}

	pthread_t job_scheduler_thread;
	pthread_t cpu_scheduler_thread;
	pthread_t cola_thread;
	clock_t inicio_programa= clock();
	pthread_create(&job_scheduler_thread,NULL, job_scheduler,(int *) connfd);
	
	pthread_create(&cpu_scheduler_thread,NULL, cpu_scheduler,(int* ) algoritmo);
	pthread_create(&cola_thread,NULL,verificar_cola ,NULL);

	pthread_join(job_scheduler_thread,NULL);
    pthread_join(cpu_scheduler_thread,NULL);
	pthread_join(cola_thread,NULL);

	display();
	clock_t end = clock();
	double time_spent = (double)(end - inicio_programa) / CLOCKS_PER_SEC;
	close(sockfd); 
}