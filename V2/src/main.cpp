#include <iostream>
#include "Entity.hpp"
#include "System.hpp"
#include "World.hpp"
#include "InputSystem.hpp"
#include "MessageHandler.hpp"
#include "GameLoader.hpp"
#include "Filter.hpp"


int main(){
    sf::RenderWindow window(sf::VideoMode(800,600), "Pacman");
    PacmanGame game(window);
    GameLoader loader(game, window);
    game.init();

    loader.run();
    return 0;
}


