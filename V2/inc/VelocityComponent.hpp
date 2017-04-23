#pragma once
#include "Component.hpp"
#include <SFML/System/Vector2.hpp>


struct VelocityComponent : Component {
    sf::Vector2f velocity;
    sf::Vector2f prevVelocity;
};
