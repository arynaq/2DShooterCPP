#pragma once
#include <SFML/Graphics.hpp>

struct CollisionResolutionEvent{
    sf::Vector2f moveBy;
    Entity entity;
    CollisionResolutionEvent(sf::Vector2f moveBy, Entity entity):
        moveBy(moveBy),entity(entity)
    {
    }
};
