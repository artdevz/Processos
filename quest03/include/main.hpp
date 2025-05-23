#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

// Definição da classe RestRoom
class RestRoom {
private:
    std::mutex mtx;
    std::condition_variable dogCond;
    std::condition_variable catCond;

    int dogsInRoom;
    int catsInRoom;

    void updateSign();

public:
    RestRoom();

    void dogWantsToEnter();
    void catWantsToEnter();

    void dogLeaves();
    void catLeaves();
};

// Funções para as threads de cachorros e gatos
void dogThread(RestRoom& room, int id);
void catThread(RestRoom& room, int id);

#endif // MAIN_HPP
