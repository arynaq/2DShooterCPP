#include "GameLoader.hpp"
#include <SFML/System/Clock.hpp>
#include <iostream>


GameLoader::GameLoader(PacmanGame& game, sf::Window& window):
    window(&window),
    game(&game)
{
}


void GameLoader::run(){
    sf::Clock clock;
    while(game->isRunning()){
        while(window->isOpen()){
            sf::Event event;
            while(window->pollEvent(event)){
                game->handleEvent(event);
            }
        }
    }
}