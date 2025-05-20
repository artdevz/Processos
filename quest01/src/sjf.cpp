#include "Scheduler.cpp"
#include <stdio.h>
#include <stdbool.h>

/*typedef struct Process
{
    int pid; //Id do processo
    int burstTime; //tempo que passa na cpu
    int arrivalTime; //tempo que ele chega
};*/

int main() {
    int n ;
    printf("Processos que tem");
    scanf("%d" , &n);

    Process p[n];

    for (int i = 0; i < n; i++){
        p[i].pid = i + 1;
        printf("Processo", p[i].pid);
        scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
    }

    int completed = 0;
    int current_time = 0;

    for( int i = 0; i < n ; i++){
        if (!p[i].done && p[i].arrivalTime)
    }
}