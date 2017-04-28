#pragma once
#include "VelocityComponent.hpp"

struct VelocityChangedEvent{
    Entity entity;
    sf::Vector2f velocity;

    VelocityChangedEvent(Entity e, sf::Vector2f velocity)
        :entity(e), velocity(velocity)
    {
    }
};
