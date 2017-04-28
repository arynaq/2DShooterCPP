#include "MovementSystem.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

void MovementSystem::update(double dt){
    auto& entities = getEntities();
    for(auto& entity : entities){
        auto& transform = entity.getComponent<TransformComponent>().transform;
        auto& velocity = entity.getComponent<VelocityComponent>().velocity;
        transform.move(velocity*(float)dt);
    }
}


void MovementSystem::receive(const CollisionResolutionEvent& event){
    if(event.entity.hasComponent<TransformComponent>()){
        auto& transform = event.entity.getComponent<TransformComponent>().transform;
        transform.move(event.moveBy);
    }
}

void MovementSystem::receive(const DirectionChangedEvent& event){
    if(event.entity.hasComponent<VelocityComponent>()){
        auto& velocityComponent = event.entity.getComponent<VelocityComponent>();

        switch(event.direction){
            case DirectionComponent::Direction::NORTH:
                velocityComponent.velocity.y = -velocityComponent.baseSpeed;
                velocityComponent.velocity.x = 0;
                break;
            case DirectionComponent::Direction::SOUTH:
                velocityComponent.velocity.y = velocityComponent.baseSpeed;
                velocityComponent.velocity.x = 0;
                break;
            case DirectionComponent::Direction::WEST:
                velocityComponent.velocity.x = -velocityComponent.baseSpeed;
                velocityComponent.velocity.y = 0;
                break;
            case DirectionComponent::Direction::EAST:
                velocityComponent.velocity.x = velocityComponent.baseSpeed;
                velocityComponent.velocity.y = 0;
                break;
        }
    }
}
