#pragma once

#include "Component.hpp"

struct CollisionComponent : Component {
    sf::FloatRect collisionBox{0,0,32,32};
};
