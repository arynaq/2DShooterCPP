#pragma once
#include "System.hpp"
#include "TransformComponent.hpp"
#include "VelocityComponent.hpp"


struct MovementSystem : System<Requires<VelocityComponent, TransformComponent>> {
    void update(double dt);
};
