#include "CollisionSystem.hpp"
#include "Events.hpp"
#include "World.hpp"
#include <iostream>




void CollisionSystem::update(double dt){
    m_dt = dt;
    auto& entities = getEntities();
    for(auto& entity : entities){
        auto& collisionComponent = entity.getComponent<CollisionComponent>();
        auto& collisionBox = collisionComponent.collisionBox;
        auto& offsetX = collisionComponent.offsetX;
        auto& offsetY = collisionComponent.offsetY;
        auto& transform = entity.getComponent<TransformComponent>().transform;
        collisionBox.left = transform.getPosition().x + offsetX;
        collisionBox.top  = transform.getPosition().y + offsetY;
    }
    for(std::size_t i=0; i<entities.size(); ++i){
        auto& left = entities[i];
        auto& leftBox = left.getComponent<CollisionComponent>().collisionBox;
        for(std::size_t j=i+1; j<entities.size(); ++j){
            auto& right = entities[j];
            auto& rightBox = right.getComponent<CollisionComponent>().collisionBox;
            if(leftBox.intersects(rightBox)){
                std::cout<<"Crash.."<<std::endl;
            }
        }
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

void CollisionSystem::receive(const TileCollisionEvent& event){
}
