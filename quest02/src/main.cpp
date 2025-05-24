#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <random>

constexpr int NUM_PROGRAMADORES = 5;

std::mutex mtx_compilador;
std::condition_variable cv_compilador;
bool compilador_livre = true;

std::mutex mtx_banco;
std::condition_variable cv_banco;
int acessos_banco = 0;
const int MAX_ACESSOS_BANCO = 2;

void programador(int id) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(500, 1500); // tempo aleatório

    while (true) {
        {
            //trava o banco até 2
            std::unique_lock<std::mutex> lock(mtx_banco);
            std::cout << "Programador " << id << " esperando acesso ao banco de dados...\n";
            cv_banco.wait(lock, [] { return acessos_banco < MAX_ACESSOS_BANCO; });
            ++acessos_banco;
            std::cout << "Programador " << id << " acessou o banco de dados.\n";
        }

        {
            //trava o compilador
            std::unique_lock<std::mutex> lock(mtx_compilador);
            std::cout << "Programador " << id << " esperando acesso ao compilador...\n";
            cv_compilador.wait(lock, [] { return compilador_livre; });
            compilador_livre = false;
        }

        std::cout << "Programador " << id << " compilando...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(dist(gen)));
        std::cout << "Programador " << id << " terminou a compilação.\n";

        {
            std::unique_lock<std::mutex> lock(mtx_compilador);
            compilador_livre = true;
            cv_compilador.notify_one();
        }

        {
            std::unique_lock<std::mutex> lock(mtx_banco);
            --acessos_banco;
            cv_banco.notify_one();
        }

        std::cout << "Programador " << id << " descansando...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(dist(gen)));
    }
}

int main() {
    std::thread programadores[NUM_PROGRAMADORES];

    for (int i = 0; i < NUM_PROGRAMADORES; ++i) {
        programadores[i] = std::thread(programador, i + 1);
    }

    for (auto& t : programadores) {
        t.join();
    }

    return 0;
}
























