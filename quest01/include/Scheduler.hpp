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
<<<<<<< HEAD

    Process(int p, int b, int a) : pid(p), burstTime(b), arrivalTime(a) {}
=======
    bool done
>>>>>>> bb939ef (Feito coisas)
};

class Scheduler {

public:
    Scheduler(int);
    void addProcess(int, int, int);
    void run(int);

private:
    int quantum;
    std::vector<Process> processes;
    void firstComeFirstServe();
    void shortestJobFirst();
    void roundRobin();
    void printQueue(const std::queue<Process>& q);

};

#endif