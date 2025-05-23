#include <iostream>
#include <random>
#include <cstdlib>
#include "Scheduler.hpp"

void plotAsciiBar(const std::string& title, const std::vector<std::pair<std::string, double>>& data) {
    std::cout << "\n" << title << "\n";
    for (const auto& d : data) {
        std::cout << d.first << " | ";
        int barLength = static_cast<int>(d.second / 2); // Ajusta escala
        for (int i = 0; i < barLength; ++i) {
            std::cout << "#";
        }
        std::cout << " (" << d.second << ")\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Args: ./quest01 <quantum>\n";
        return 1;
    }

    int quantum = std::atoi(argv[1]);
    std::cout << "Questão 1 (C++)!" << std::endl;
    
    Scheduler scheduler(quantum); 

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
    scheduler.addProcess(1000, T1, 0); 
    scheduler.addProcess(2000, T2, 20);
    scheduler.addProcess(3000, T3, 10);
    scheduler.addProcess(4000, T4, 15);

    scheduler.run(1);
    scheduler.run(2);
    scheduler.run(3);

    std::vector<std::pair<std::string, double>> waitData = {
        {"FCFS", scheduler.metrics[0].averageWaitingTime},
        {"SJF ", scheduler.metrics[1].averageWaitingTime},
        {"RR  ", scheduler.metrics[2].averageWaitingTime}
    };
    
    std::vector<std::pair<std::string, double>> turnaroundData = {
        {"FCFS", scheduler.metrics[0].averageTurnaroundTime},
        {"SJF ", scheduler.metrics[1].averageTurnaroundTime},
        {"RR  ", scheduler.metrics[2].averageTurnaroundTime}
    };
    
    std::vector<std::pair<std::string, double>> throughputData = {
        {"FCFS", scheduler.metrics[0].throughput},
        {"SJF ", scheduler.metrics[1].throughput},
        {"RR  ", scheduler.metrics[2].throughput}
    };
    
    plotAsciiBar("Tempo Médio de Espera", waitData);
    plotAsciiBar("Tempo Médio de Retorno", turnaroundData);
    plotAsciiBar("Vazão (Throughput)", throughputData);

    return 0;
}