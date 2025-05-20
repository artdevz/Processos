#include "Scheduler.hpp"

Scheduler::Scheduler(int quantum) : quantum(quantum) {}

void Scheduler::addProcess(int pid, int burstTime, int arrivalTime) {
    Process p;
    p.pid = pid;
    p.burstTime = burstTime;
    p.arrivalTime = arrivalTime;
    p.done = false;

    processes.push_back(p);
}

void Scheduler::run(int algorithm) {
    switch (algorithm) {
        case 1: // FCFS
            std::cout << "Algoritmo First Come First Serve!" << std::endl;
            firstComeFirstServe();
            break;
        case 2: // SJF
            std::cout << "Algoritmo Shortest Job First!" << std::endl;
            shortestJobFirst();
            break;
        case 3: // Round Robin
            std::cout << "Algoritmo Round Robin!" << std::endl;
            roundRobin();
            break;
        default:
            std::cout << "Algoritmo inválido!" << std::endl;
    }
}

void Scheduler::firstComeFirstServe() {
    int time = 0;

    for (auto& p : processes) {
        std::cout << "Processo " << p.pid << " chegou em Tempo " << p.arrivalTime << " com Burst de " << p.burstTime << "\n";
        time += p.burstTime;
        std::cout << "Processo " << p.pid << " finalizado no Tempo " << time << ".\n";
    }

    std::cout << "Todos os processos foram executados!\n";
}

void Scheduler::shortestJobFirst(){
    int time = 0;

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
while (completed < n)
{
    int indice = 0;
    int mini_burst = 0;

    for( int i = 0; i < n ; i++){
        if (!p[i].done && p[i].arrivalTime <= current_time){
            if(p[i].burstTime < mini_burst){
                mini_burst = p[i].burstTime;
                indice = i;
            }
        }
    }

    if (indice == 0){
        current_time ++;
        continue;
    }
}

}

void Scheduler::shortestJobFirst() {
    std::cout << "[SJF executado]\n";
}

void Scheduler::roundRobin() {
    std::cout << "[RR executado com quantum = " << quantum << "]\n";
}

void Scheduler::printQueue(const std::queue<Process>& q) {
    std::cout << "[Fila de processos]\n";
}