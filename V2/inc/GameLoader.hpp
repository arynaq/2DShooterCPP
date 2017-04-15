#pragma once
#include <SFML/Graphics.hpp>
#include "PacmanGame.hpp"


class GameLoader {

    public:
        GameLoader(PacmanGame& game, sf::Window& window);
        void run();
    private:
        sf::Window* window;
        PacmanGame* game;
};
