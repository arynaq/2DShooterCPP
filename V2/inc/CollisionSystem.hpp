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
    void update(MapSystem& map, double dt);
    double m_dt;

private:
    void checkTileCollision(MapSystem& map, Entity& entity);
    
};
