#include <iostream>
#include <random>
#include "Scheduler.hpp"

int main() {
    std::cout << "Questão 1 (C++)!" << std::endl;
    Scheduler scheduler(50); // Equilíbrio
    // 80 = Fluído
    // < 30 = Overhead
    // > 100 = Pouca alternância

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distT1(10, 30);
    int T1 = distT1(gen);

    std::uniform_int_distribution<> distT2(T1 + 10, T1 + 50);
    int T2 = distT2(gen);

    std::uniform_int_distribution<> distT3(T2 + 100, T2 + 200);
    int T3 = distT3(gen);

    std::uniform_int_distribution<> distT4(T3 + 10, T3 + 50);
    int T4 = distT4(gen);

    // PID, Burst Time, Arrival Time
    scheduler.addProcess(100, T1, 0); 
    scheduler.addProcess(200, T2, 30);
    scheduler.addProcess(300, T3, 20);
    scheduler.addProcess(400, T4, 25);

    scheduler.run(1);
    scheduler.run(2);
    scheduler.run(3);

    return 0;
}