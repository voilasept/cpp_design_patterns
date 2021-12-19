#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include <sstream>
#include <boost/signals2.hpp>
using namespace std;

/*
 * Far from CPU affinity. MacOS doesn't support it.
 */

class Game{
public:
    mutex mtx;
    Game() = default;
    boost::signals2::signal<void(string&)> event_driver;
};

class Player{
public:
    Player(size_t id, Game& game):id(id), game(game) {
        game.event_driver.connect(
                [&](string& msg){ this->on_receive_message(msg); });
    }
    size_t id;
    Game& game;
    void on_receive_message(string& msg) const {
        game.mtx.lock();
        cout << "threadID: " << this_thread::get_id()
             << ", playerID: " << id << " === " << msg << endl;
        game.mtx.unlock();
        this_thread::sleep_for(chrono::seconds (1));
    }
    void notify(string&& string){
        game.event_driver(string);
    }
};

[[noreturn]] void event_loop(Player& player){
    int counter = 0;
    ostringstream oss;
    while(true){
        this_thread::sleep_for(chrono::seconds(2));
        oss.str("");  oss.clear();       // step1 is clear the string content, step2 is clear any error flag
        oss << "COUNTER "s + to_string(counter) + " FROM PLAYER " << player.id << endl;
        player.notify(oss.str());
        counter++;
    }
}

// add player init wait time
int main() {
    Game game {};
    Player player1 {0, game};
    Player player2 {1, game};
    thread t1 ([&](){ event_loop(player1); });
    thread t2 ([&](){ event_loop(player2); });
    t1.join();
    t2.join();
    return 0;
}
