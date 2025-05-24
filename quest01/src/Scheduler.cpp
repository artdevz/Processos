#include <limits>
#include <algorithm>
#include "Scheduler.hpp"

Scheduler::Scheduler(int quantum) : quantum(quantum) {}

void Scheduler::addProcess(int pid, int burstTime, int arrivalTime) {
    Process p;
    p.pid = pid;
    p.burstTime = burstTime;
    p.arrivalTime = arrivalTime;
    p.remainingTime = burstTime;
    p.done = false;

    processes.push_back(p);
}

void Scheduler::run(int algorithm) {
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    switch (algorithm) {
        case 1: // FCFS
            std::cout << "\nAlgoritmo First Come First Serve!" << std::endl;
            firstComeFirstServe();
            break;
        case 2: // SJF
            std::cout << "\nAlgoritmo Shortest Job First!" << std::endl;
            shortestJobFirst();
            break;
        case 3: // Round Robin
            std::cout << "\nAlgoritmo Round Robin!" << std::endl;
            std::cout << "Quantum: " << quantum << std::endl;
            roundRobin();
            break;
        default:
            std::cout << "Algoritmo inválido!" << std::endl;
    }
}

void Scheduler::firstComeFirstServe() {
    int time = 0, waitingTime = 0, turnaroundTime = 0, throughput = 0, throughputTime = 100, processesCount = 0;
    processesCount = processes.size();

    for (auto& p : processes) {
        if (time < p.arrivalTime) time = p.arrivalTime;

        std::cout << "[" << time << "]: Processo " << p.pid << " chegou em Tempo " << p.arrivalTime << " com Burst de " << p.burstTime << std::endl;
        waitingTime += time - p.arrivalTime;
        time += p.burstTime;
        std::cout << "[" << time << "]: Processo " << p.pid << " finalizou!\n";
        turnaroundTime += time - p.arrivalTime;
        if (time <= throughputTime) throughput++;
        time += contextSwitches;
    }

    // std::cout << "\nMétricas: " << std::endl;
    // std::cout << "ProcessesCount: " << processesCount << std::endl;
    // std::cout << "Total Waiting Time: " << waitingTime << std::endl;
    // std::cout << "Average Waiting Time: " << (double) waitingTime / processesCount << std::endl;
    // std::cout << "Total Turnaround Time: " << turnaroundTime << std::endl;
    // std::cout << "Average Turnaround Time: " << turnaroundTime / processesCount << std::endl;
    // std::cout << "Throughput: " << throughput << std::endl;

    std::cout << "Todos os processos foram executados!\n";

    SchedulingMetrics sm;
    sm.averageWaitingTime = (double) waitingTime / processesCount;
    sm.averageTurnaroundTime = (double) turnaroundTime / processesCount;
    sm.throughput = (double) throughput;
    metrics.push_back(sm);
}

void Scheduler::shortestJobFirst() {
    int n = processes.size();
    int completed = 0;
    int current_time = 0, waitingTime = 0, turnaroundTime = 0, throughput = 0, throughputTime = 100, processesCount = 0;
    processesCount = n;
    std::vector<bool> done(n, false);

    while (completed < n) {
        int indice = -1;
        int mini_burst = std::numeric_limits<int>::max();;

        for (int i = 0; i < n; i++) {
            if (!done[i] && processes[i].arrivalTime <= current_time) {
                if (processes[i].burstTime < mini_burst) {
                    mini_burst = processes[i].burstTime;
                    indice = i;
                }
            }
        }

        if (indice == -1) {
            current_time++;
            continue;
        }

        if (current_time < processes[indice].arrivalTime) current_time = processes[indice].arrivalTime;

        std::cout << "[" << current_time << "]: Processo " << processes[indice].pid
                  << " chegou em Tempo " << processes[indice].arrivalTime
                  << " com Burst de " << processes[indice].burstTime << " \n";
        waitingTime += current_time - processes[indice].arrivalTime;
        // std::cout << "Waiting Time: " << waitingTime << std::endl;
        std::cout << "[" << (current_time + processes[indice].burstTime) << "]: Processo " << processes[indice].pid
                  << " finalizou.\n";
        turnaroundTime += current_time - processes[indice].arrivalTime + processes[indice].burstTime;
        // std::cout << "Turnaround Time: " << turnaroundTime << std::endl;
        
        current_time += processes[indice].burstTime;
        if (current_time <= throughputTime) throughput++;
        current_time += contextSwitches;
        done[indice] = true;
        completed++;
    }

    // std::cout << "\nMétricas: " << std::endl;
    // std::cout << "ProcessesCount: " << processesCount << std::endl;
    // std::cout << "Total Waiting Time: " << waitingTime << std::endl;
    // std::cout << "Average Waiting Time: " << (double) waitingTime / processesCount << std::endl;
    // std::cout << "Total Turnaround Time: " << turnaroundTime << std::endl;
    // std::cout << "Average Turnaround Time: " << turnaroundTime / processesCount << std::endl;
    // std::cout << "Throughput: " << throughput << std::endl;

    std::cout << "Todos os processos foram executados!\n";

    SchedulingMetrics sm;
    sm.averageWaitingTime = (double) waitingTime / processesCount;
    sm.averageTurnaroundTime = (double) turnaroundTime / processesCount;
    sm.throughput = (double) throughput;
    metrics.push_back(sm);
}

void Scheduler::roundRobin() {
    int time = 0, waitingTime = 0, turnaroundTime = 0, throughput = 0, throughputTime = 100, processesCount = 0;
    processesCount = processes.size();

    while (!processes.empty()) {
        auto&p = processes.front();

        if (time < p.arrivalTime) time = p.arrivalTime;

        std::cout << "[" << time << "]: Processo " << p.pid << " chegou em Tempo " << p.arrivalTime << " com Burst de " << p.burstTime << " e resta " << p.remainingTime << std::endl;
        waitingTime += time - p.arrivalTime - (p.burstTime - p.remainingTime); // (Burst - Remaining): Para não contabilizar no tempo de espera um tempo que estava sendo executado
        p.remainingTime -= quantum;

        if (p.remainingTime <= 0) {
            time += quantum + p.remainingTime;
            std::cout << "[" << time << "]: Processo " << p.pid << " finalizou!\n";
            turnaroundTime += time - p.arrivalTime;
            if (time <= throughputTime) throughput++;
            processes.erase(processes.begin());
            time += contextSwitches;
            continue;
        }

        time += quantum;
        std::cout << "[" << time << "]: Processo " << p.pid << " teve seu Quantum esgotado restando: " << p.remainingTime << std::endl;
        std::cout << "[" << time << "]: Processo " << p.pid << " está sendo deslocado pro final da fila\n";
        processes.push_back(processes.front());
        processes.erase(processes.begin());
        time += contextSwitches;
    }

    // std::cout << "\nMétricas: " << std::endl;
    // std::cout << "ProcessesCount: " << processesCount << std::endl;
    // std::cout << "Total Waiting Time: " << waitingTime << std::endl;
    // std::cout << "Average Waiting Time: " << (double) waitingTime / processesCount << std::endl;
    // std::cout << "Total Turnaround Time: " << turnaroundTime << std::endl;
    // std::cout << "Average Turnaround Time: " << turnaroundTime / processesCount << std::endl;
    // std::cout << "Throughput: " << throughput << std::endl;

    std::cout << "Todos os processos foram executados!\n";

    SchedulingMetrics sm;
    sm.averageWaitingTime = (double) waitingTime / processesCount;
    sm.averageTurnaroundTime = (double) turnaroundTime / processesCount;
    sm.throughput = (double) throughput;
    metrics.push_back(sm);
}