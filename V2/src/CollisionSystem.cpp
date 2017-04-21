#include "CollisionSystem.hpp"
#include "Events.hpp"
#include "World.hpp"
#include <iostream>


void CollisionSystem::update(double dt){
    auto& entities = getEntities();
    for(std::size_t i=0; i<entities.size(); ++i){
        auto& entity = entities[i];
        auto& collisionBox = entity.getComponent<CollisionComponent>().collisionBox;
        auto& transform = entity.getComponent<TransformComponent>().transform;
        collisionBox.left = transform.getPosition().x;
        collisionBox.top  = transform.getPosition().y;
    }

    /**
    for(std::size_t i=0; i<entities.size(); ++i){
        auto& left = entities[i];
        auto& leftCollisionBox = left.getComponent<CollisionComponent>().collisionBox;
        for(std::size_t j=i+1; j<entities.size(); ++j){
            auto& right = entities[j];
            auto& rightCollisionBox = right.getComponent<CollisionComponent>().collisionBox;
            if(leftCollisionBox.intersects(rightCollisionBox)){
                std::cout<<"Collision..."<<std::endl;
                getWorld().messageHandler().emit<CollisionEvent>(left, right);
            }
        }
    }
    **/

}


