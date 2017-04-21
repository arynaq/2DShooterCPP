#pragma once
#include "System.hpp"
#include "TransformComponent.hpp"
#include "VelocityComponent.hpp"
#include "MessageHandler.hpp"
#include "CollisionEvent.hpp"


struct MovementSystem : System<Requires<VelocityComponent, TransformComponent>>, Receiver<MovementSystem> {
    void update(double dt);
    void receive(const CollisionEvent& event);
};
