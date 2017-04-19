#include "GameLoader.hpp"
#include "Clock.hpp"

GameLoader::GameLoader(PacmanGame& game, sf::Window& window):
    window(&window),
    game(&game)
{
}


void GameLoader::run(){
    using Second = double;
    using WallClock = Clock<Second>;
    using Event = sf::Event;


    Event event;
    Second start = WallClock::now();
    Second total = 0;
    Second framedt = game->frame_dt;

    while(game->isRunning()){
        while(window->pollEvent(event)){
            game->handleEvent(event);
        }

        Second now = WallClock::now();
        Second delta = now - start;
        total += delta;

        while(total >= framedt) {
            total -= framedt;
            game->update(framedt);
        }

        game->render();
        window->display();
        start = now;
    }
}
