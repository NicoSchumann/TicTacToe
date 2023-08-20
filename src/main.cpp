#include "Game.hpp"
#include <thread>


int main()
{
    Game * game = new Game();
    std::thread t(&Game::run, std::ref(*game));
    if(t.joinable()) t.join();
}
