#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <vector>

class RestRoom{
public:
    std::mutex mutex;
    std::condition_variable dogCond;
    std::condition_variable catCond;
    int dogs_in_room = 0;
    int casts_in_room = 0;

    void updateSign() {
        if (dogs_in_room > 0) {
            std::cout << "Cachorros presentes (" << dogs_in_room << ")\n";
        } else if (casts_in_room > 0) {  // corrigido aqui
            std::cout << "Gatos presentes (" << casts_in_room << ")\n";
        } else {
            std::cout << "Vazia\n";
        }
    }

    void dogsWantEnter(int id){
        std::unique_lock<std::mutex> lock(mutex);
        while(casts_in_room > 0){
            dogCond.wait(lock);
        }
        dogs_in_room++;
        std::cout << "Cachorro " << id << " entrou.\n";  
        updateSign();
    }

    void catWantsToEnter(int id) {
        std::unique_lock<std::mutex> lock(mutex);
        while (dogs_in_room > 0) {
            catCond.wait(lock);
        }
        casts_in_room++;
        std::cout << "Gato " << id << " entrou.\n";  
        updateSign();
    }

    void dogLeaves() {
        std::unique_lock<std::mutex> lock(mutex);
        dogs_in_room--;
        if (dogs_in_room == 0) {
            catCond.notify_all();
        }
        updateSign();
    }

    void catLeaves() {
        std::unique_lock<std::mutex> lock(mutex);
        casts_in_room--;
        if (casts_in_room == 0) {
            dogCond.notify_all();
        }
        updateSign();
    }
};

void dogThread(RestRoom& room, int id) {
    room.dogsWantEnter(id);
    std::this_thread::sleep_for(std::chrono::milliseconds(500 + (id * 100)));
    room.dogLeaves();
    std::cout << "Cachorro " << id << " saiu.\n";
}

void catThread(RestRoom& room, int id) {
    room.catWantsToEnter(id);
    std::this_thread::sleep_for(std::chrono::milliseconds(400 + (id * 150)));
    room.catLeaves();
    std::cout << "Gato " << id << " saiu.\n";
}

int main() {
    RestRoom room;
    std::vector<std::thread> threads;

    for (int i = 0; i < 3; ++i) {
        threads.emplace_back(dogThread, std::ref(room), i + 1);
    }

    for (int i = 0; i < 3; ++i) {
        threads.emplace_back(catThread, std::ref(room), i + 1);
    }

    for (auto& t : threads)
        t.join();

    return 0;
}
