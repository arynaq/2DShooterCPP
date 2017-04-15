#pragma once
#include "System.hpp"
#include "PlayerComponent.hpp"
#include "VelocityComponent.hpp"

struct InputSystem : System<Requires<PlayerComponent, VelocityComponent>> {
    public:
        void update();
        ~InputSystem(){}
};
