#pragma once
#include "DirectionComponent.hpp"

struct DirectionChangedEvent{
    Entity entity;
    DirectionComponent::Direction direction;

    DirectionChangedEvent(Entity e, DirectionComponent::Direction direction):
        entity(e),direction(direction)
    {
    }
};
