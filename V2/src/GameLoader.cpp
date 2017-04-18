#include "GameLoader.hpp"
#include <SFML/System/Clock.hpp>

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
                game->update(1);
                game->render();
            }
        }
    }
}
