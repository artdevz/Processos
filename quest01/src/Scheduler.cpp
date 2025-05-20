#include "Scheduler.hpp"
#include <limits>
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

void Scheduler::shortestJobFirst() {
    int n = processes.size();
    int completed = 0;
    int current_time = 0;
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

        std::cout << "Processo " << processes[indice].pid
                  << " chegou em Tempo " << processes[indice].arrivalTime
                  << " com Burst de " << processes[indice].burstTime << "\n";
        std::cout << "Processo " << processes[indice].pid
                  << " finalizado no Tempo " << (current_time + processes[indice].burstTime) << ".\n";

        current_time += processes[indice].burstTime;
        done[indice] = true;
        completed++;
    }

    std::cout << "Todos os processos foram executados!\n";
}

void Scheduler::roundRobin() {
    std::cout << "[RR executado com quantum = " << quantum << "]\n";
}

void Scheduler::printQueue(const std::queue<Process>& q) {
    std::cout << "[Fila de processos]\n";
}