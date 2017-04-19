#pragma once

#include "Component.hpp"

struct CollisionComponent : Component {
    struct Data {
        bool doesCollide = false;
        sf::FloatRect collisionBox;
    } data;
};
