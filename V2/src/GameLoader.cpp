#include "GameLoader.hpp"
#include "Clock.hpp"
#include <iomanip>

GameLoader::GameLoader(PacmanGame& game, sf::Window& window):
    window(&window),
    game(&game)
{
}


void GameLoader::run(){
    using Second = double;
    using WallClock = Clock<Second>;

    sf::Event event;
    Second start = WallClock::now();
    Second total = 0;
    Second framedt = game->frame_dt;
    bool doRender = false;


    while(game->isRunning()){
        game->handleEvent(event);
        while(window->pollEvent(event)){
            game->handleEvent(event);
        }

        Second now = WallClock::now();
        Second delta = now - start;
        total += delta;

        if(total >=framedt)
            doRender = true;
        else
            doRender = false;

        while(total >= framedt) {
            total -= framedt;
            game->update(framedt);
        }
        if(doRender){
            //std::cout<<"Rendering at: " << std::fixed<<WallClock::now()<<std::endl;
            game->render();
            window->display();
        }
        start = now;
    }
}
