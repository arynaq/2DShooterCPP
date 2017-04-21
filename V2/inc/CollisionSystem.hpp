#pragma once

#include "System.hpp"
#include "Components.hpp"

struct CollisionSystem : System<Requires<CollisionComponent, TransformComponent>> {
    void update(double dt);
};
