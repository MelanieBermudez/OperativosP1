#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    int n, exeTime[100],wTime=0,tAT=0;
    int i,j,temp;
    float aWT, _aWT=0, aTAT,_aTAT=0;
    printf("Enter de number of processes: ");
    scanf("%d",&n);

    for (i=0;i<n;i++){
        printf("Enter de burst time of process %d: ", i+1);
        scanf("%d",&exeTime[i]);
    }
    //arrange in ascending order
    for (i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(exeTime[i]<exeTime[j]){
                temp=exeTime[i];
                exeTime[i]= exeTime[j];
                exeTime[j]=temp;

            }
        }

    }

    printf("\nPid\t\tBt\t\tWT\t\tTAT");
    for(i=0;i<n;i++){
        tAT= exeTime[i]+wTime;
        printf("\n%d\t\t%d\t\t%d\t\t%d",i,exeTime[i],wTime,tAT);
        _aWT +=wTime;
        _aTAT += tAT;
        wTime +=exeTime[i];

    }
    aWT = _aWT/n;
    aTAT = _aTAT/n;
    printf("\n\n Average waiting time: %f",aWT);
    printf("\n\n Average turnaround time: %f",aTAT);


}