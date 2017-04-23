#pragma once

#include "System.hpp"
#include "Components.hpp"
#include "Events.hpp"
#include "MessageHandler.hpp"
#include "MapSystem.hpp"


struct MovementSystem : System<Requires<VelocityComponent, TransformComponent>>, Receiver<MovementSystem> {
    void update(MapSystem& map, double dt);
    void receive(const CollisionResolutionEvent& event);
};
