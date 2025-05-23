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
class Scheduler {

public:
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
    void printQueue(const std::queue<Process>& q);

};

#endif