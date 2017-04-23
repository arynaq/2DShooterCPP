#pragma once

#include "System.hpp"
#include "Components.hpp"
#include "MapSystem.hpp"
#include "MessageHandler.hpp"
#include "Events.hpp"

struct CollisionSystem:
    System<Requires<CollisionComponent, TransformComponent, VelocityComponent>>,
    Receiver<CollisionSystem>
{
    void receive(const TileCollisionEvent& event);
    void update(double dt);
    double m_dt;
};
