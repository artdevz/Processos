#include "Scheduler.hpp"

Scheduler::Scheduler(int quantum) : quantum(quantum) {}

void Scheduler::addProcess(int pid, int burstTime, int arrivalTime) {}

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
    std::cout << "[FCFS executado]\n";
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