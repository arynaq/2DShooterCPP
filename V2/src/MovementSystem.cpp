#include "MovementSystem.hpp"
#include <iostream>

void MovementSystem::update(MapSystem& map, double dt){
    auto& entities = getEntities();
    for(auto& entity : entities){
        auto& transform = entity.getComponent<TransformComponent>().transform;
        auto& velocity = entity.getComponent<VelocityComponent>().velocity;
        if(!map.checkTileCollision(entity)){
            transform.move(velocity*(float)dt);
        }
    }
}


void MovementSystem::receive(const CollisionResolutionEvent& event){
    auto& transform = event.entity.getComponent<TransformComponent>().transform;
    transform.move(event.moveBy);
}
