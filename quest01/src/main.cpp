#include <iostream>
#include "Scheduler.hpp"

int main() {
    std::cout << "Questão 1 (C++)!" << std::endl;
    Scheduler scheduler(4);

    scheduler.addProcess(100, 8, 0); // Processo 1, Burst Time: 8, Arrival Time: 0
    scheduler.addProcess(200, 9, 0);
    scheduler.addProcess(300, 4, 4);
    scheduler.addProcess(400, 2, 8);

    int algorithmChoice;
    std::cout << "Escolha o algoritmo de escalonamento: \n";
    std::cout << "1 - FCFS\n";
    std::cout << "2 - SJF\n";
    std::cout << "3 - Round Robin\n";
    std::cin >> algorithmChoice;

    scheduler.run(algorithmChoice);

    return 0;
}