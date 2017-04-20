#pragma once

#include "Component.hpp"

struct CollisionComponent : Component {
    sf::FloatRect collisionBox;
};
