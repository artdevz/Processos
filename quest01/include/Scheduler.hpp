#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <vector>
#include <queue>
#include <iostream>

struct Process {
    int pid;
    int burstTime;
    int arrivalTime;
    int remainingTime; // RR
    bool done;
};

struct SchedulingMetrics {
    double averageWaitingTime;      // Tempo Médio de Espera
    double averageTurnaroundTime;   // Tempo Médio de Retorno
    double throughput;              // Vazão
};

class Scheduler {

public:
    std::vector<SchedulingMetrics> metrics;
    Scheduler(int);
    void addProcess(int, int, int);
    void run(int);

private:
    int quantum;
    int contextSwitches = 1;
    std::vector<Process> processes;    
    void firstComeFirstServe();
    void shortestJobFirst();
    void roundRobin();

};

#endif