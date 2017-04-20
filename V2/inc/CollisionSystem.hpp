#pragma once

#include "System.hpp"

struct CollionSystem : System<Requires<CollisionComponent>> {
    void update(double dt);
};
