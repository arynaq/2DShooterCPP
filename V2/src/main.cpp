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
	std::cout << "Demo for the ECS - Pacman project" << std::endl << std::endl;
	std::cout << "By Aryan Naqid @HiOA @DAVE3604 - Effective C/C++ programming." << std::endl << std::endl;
	std::cout << "**Movement: wasd keys." << std::endl;
	std::cout << "**Bugs: One or both of the ghosts MAY get stuck/glued to the wall." << std::endl;
	std::cout << "**It is on @TODO list but hopefully the code and this small demonstration speaks for itself." << std::endl;
    sf::RenderWindow window(sf::VideoMode(1024,1024), "Pacman");
    PacmanGame game(window);
    GameLoader loader(game, window);
    game.init();
    loader.run();


    return EXIT_SUCCESS;

}

