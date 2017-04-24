#pragma once

#include "Component.hpp"

struct CollisionComponent : Component {
    sf::FloatRect collisionBox{2,2,27,30};
};
