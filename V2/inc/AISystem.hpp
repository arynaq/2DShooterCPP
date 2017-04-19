#pragma once
#include "System.hpp"
#include "AIComponent.hpp"

struct AISystem : System<Requires<AIComponent>> {
    void update(double dt){

    }
}
