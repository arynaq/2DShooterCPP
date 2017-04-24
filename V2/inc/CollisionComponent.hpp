#pragma once

#include "Component.hpp"

struct CollisionComponent : Component {
    float offsetX = 2;
    float offsetY = 2;
    sf::FloatRect collisionBox{offsetX,offsetY,27,30};
};
