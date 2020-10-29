#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <math.h>
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <stdbool.h>

#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 

int cantidad_procesos_realizados, cpu_ocioso;
int algoritmo;
int quantum = 0; 
int procesos_cola;
int cant_procesos=0;

int sumw=0,sumt=0;
int wt=0;
int x = 0;
float avgwt=0.0,avgta=0.0;

 
typedef struct proceso {
	int pid;
	int burst;
	int priority;
	bool estado;
	int ejecutado;
	int wt,ta;
	int flag;
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
proceso_ptr pop()
{
	proceso_ptr temp = front;
	front = front->anterior;
	return temp;

}
 
void display(){
	if(is_empty()){
		printf("\nCola Ready Vacia\n");
		return;
	}
	proceso_ptr temp = front;
	printf("\n Cola Ready \n Procesos:  ");
	while(temp != NULL){
		printf("[%d]", temp->pid);
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



void HPF()
{
	int cant_cola = cola_size();
	int n = 0;
	n = procesos_cola;
	int sumw=0,sumt=0;
	float avgwt=0.0,avgta=0.0;
	int i,j;
	int x = 0;
	proceso_ptr temp = front;
	proceso_ptr t;
		for(i=2;i<n;i++)
		for(j=1;j<n-i+1;j++){
			if(temp->priority > temp->anterior->priority){
				t = temp;
				temp = temp->anterior;
				temp->anterior = t;
			}
		}
	printf("\n\n PROC.\tB.T.");
		for(i=0;i<n;i++)
			printf("\n %d\t%d",temp->pid,temp->burst);

		sumw = temp->wt = 0;
		sumt = temp->ta = temp->burst;

		for(i=1;i<n;i++){
			temp->wt = (temp[i-1].burst + temp[i-1].wt);
			temp->ta = (temp->wt + temp->burst);
			sumw+=temp->wt;
			sumt+=temp->ta;
		}
		avgwt = (float)sumw/n;
		avgta = (float)sumt/n;
		printf("\n\n PROC.\tB.T.\tW.T\tT.A.T");
		for(i=0;i<n;i++)
			printf("\n %s\t%d\t%d\t%d",temp->pid,temp->burst,temp->wt,temp->ta);
		
		printf("\n\n GANTT CHART\n ");
		for(i=0;i<n;i++)
			printf("   %s   ",temp->pid);
			printf("\n ");
			printf("0\t");

		for(i=1;i<=n;i++){
			x+=temp[i-1].burst;
			printf("%d      ",x);
		}
		//printf("\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.",avgwt,avgta);

}
void SJF(){
	int sumw=0,sumt=0;
	int x = 0;
	float avgwt=0.0,avgta=0.0;
	int i,j;
}
void RR(){
	int pflag=0,t,tcurr=0,k,i,Q=0;
	int sumw=0,sumt=0;
	float avgwt=0.0,avgta=0.0;
}

void FCFS(){

	int cant_cola = cola_size();
	int n = 0;
	n = procesos_cola;
	proceso_ptr temp = front;
	sleep(5);
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
			printf("Proceso ejecutado terminado:  %d\n", temp_proccess2->pid);
			push_ejecutados(*temp_proccess2);
		}
		printf("Ejecutando proceso: %d Burst: %d Prioridad: %d \n", temp->pid ,temp->burst, temp->priority );
		sleep(temp->burst);
		temp->wt = wt; 
		temp->ta =  temp->wt +  temp->burst;
		cant_cola--;

		proceso_ptr temp_proccess2 = (proceso_ptr) malloc(sizeof (struct proceso));
		temp_proccess2= pop();
		printf("\nProceso ejecutado terminado: %d \n", temp_proccess2->pid);
		push_ejecutados(*temp_proccess2);


		
		printf("\n\n PROC.\tB.T.\tW.T\tT.A.T");
		proceso_ptr temp1 = proc_ejecutados_front;
		while(temp1->anterior != NULL){
			printf("\n %d\t%d\t%d\t%d",temp1->pid,temp1->burst,temp1->wt,temp1->ta);
			temp1 = temp1->anterior;
		}
		printf("\n %d\t%d\t%d\t%d",temp1->pid,temp1->burst,temp1->wt,temp1->ta);
		
		
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
			temp_proccess->ejecutado=0;
			procesos_cola++;
			cant_procesos++;
			
			push(*temp_proccess);

		}
		//NO BORRAR : CODIGO DE POP
		// proceso_ptr temp_proccess2 = (proceso_ptr) malloc(sizeof (struct proceso));
		// temp_proccess2= pop();
		// printf("POP: %d", temp_proccess2->pid);	
		 
			// pthread_exit(0);
	} 
}

void *cpu_scheduler(void *algoritmo){
	int n; 
	for(;;){
		if (algoritmo ==1){
			if(is_empty()){
				int a =1;
				//printf("\nThe queue is empty!\n");
			}else{
				FCFS();
				//display_ejecutados();
				avgwt = (float)sumw/cant_procesos;
				avgta = (float)sumt/cant_procesos;
				printf("\n\n Average waiting time = %0.2f - Average turn-around = %0.2f.",avgwt,avgta);
			}
		}
		else if (algoritmo ==2){
			printf("SJF");
		}
		else if (algoritmo ==3){
			printf("HPF");
		}
		else if (algoritmo ==4){
			printf("Round Robin");
			printf("\nIngrese el quantum: ");
			scanf("%d", &quantum);
		}
	}
	
}
void* verificar_cola(){
	int n;
	for(;;){
		scanf("%d", &n);
		if(n==5){
			display();
		}
		else if(n==7){
			display_ejecutados();
		}
		else if(n==6){
			break;
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
    printf("\n 2. SJF ");
    printf("\n 3. HPF ");
    printf("\n 4. ROUND ROBIN");
	printf("\n 5. Verificar la cola\n");
	printf("\n 6. Terminar la ejecucion\n");
	
	scanf("%d", &algoritmo);

	pthread_t job_scheduler_thread;
	pthread_t cpu_scheduler_thread;
	pthread_t cola_thread;
	
	pthread_create(&job_scheduler_thread,NULL, job_scheduler,(int *) connfd);
	pthread_create(&cpu_scheduler_thread,NULL, cpu_scheduler,(int* ) algoritmo);
	pthread_create(&cola_thread,NULL,verificar_cola ,NULL);

	pthread_join(job_scheduler_thread,NULL);
    pthread_join(cpu_scheduler_thread,NULL);
	pthread_join(cola_thread,NULL);

	display();

	close(sockfd); 
}