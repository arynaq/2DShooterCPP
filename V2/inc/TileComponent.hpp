#pragma once
#include "Component.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

struct TileComponent : Component{
    sf::RectangleShape shape{sf::Vector2f(32,32)};
}; 
