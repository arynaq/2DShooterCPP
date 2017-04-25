#pragma once
#include "Component.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <utility>

struct TileComponent : Component{
    sf::RectangleShape shape{sf::Vector2f(32,32)};
    std::pair<std::size_t, std::size_t> index;
    bool passable = false;
}; 
