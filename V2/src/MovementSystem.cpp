#include "MovementSystem.hpp"
#include <iostream>


void MovementSystem::update(double dt){
    auto& entities = getEntities();
    for(auto& entity : entities){
        auto& transform = entity.getComponent<TransformComponent>().transform;
        auto& velocity = entity.getComponent<VelocityComponent>().velocity;

        transform.move(velocity*(float)dt);
    }
}
