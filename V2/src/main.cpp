#include <iostream>
#include "Entity.hpp"
#include "System.hpp"
#include "World.hpp"
#include "InputSystem.hpp"
#include "GameLoader.hpp"
#include "MessageHandler.hpp"
#include "Filter.hpp"
#include "config.h"


int main(){
    sf::RenderWindow window(sf::VideoMode(1024,1024), "Pacman");
    PacmanGame game(window);
    GameLoader loader(game, window);
    game.init();
    loader.run();
    return 0;
}


