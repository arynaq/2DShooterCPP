#pragma once

#include "System.hpp"
#include "Components.hpp"
#include "Events.hpp"
#include "MessageHandler.hpp"
#include "MapSystem.hpp"


struct MovementSystem : System<Requires<VelocityComponent, TransformComponent>>, Receiver<MovementSystem> {
    void update(double dt);
    void receive(const CollisionEvent& event);
};
