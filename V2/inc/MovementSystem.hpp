#pragma once

#include "System.hpp"
#include "Components.hpp"
#include "Events.hpp"
#include "MessageHandler.hpp"


struct MovementSystem : System<Requires<VelocityComponent, TransformComponent>>, Receiver<MovementSystem> {
    void update(double dt);
    void receive(const CollisionResolutionEvent& event);
    void receive(const DirectionChangedEvent& event);
};
