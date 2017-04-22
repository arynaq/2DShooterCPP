#pragma once

#include "System.hpp"
#include "Components.hpp"
#include "MapSystem.hpp"
#include "MessageHandler.hpp"
#include "Events.hpp"

struct CollisionSystem:
    System<Requires<CollisionComponent, TransformComponent>>,
    Receiver<CollisionSystem>
{
    void receive(const TileCollisionEvent& event);
    void update(MapSystem& map, double dt);
};
