#pragma once
#include "System.hpp"
#include "Events.hpp"
#include "Components.hpp"
#include "MessageHandler.hpp"

struct InputSystem : System<Requires<PlayerComponent, VelocityComponent>>{
    void update();
    ~InputSystem(){}
};
