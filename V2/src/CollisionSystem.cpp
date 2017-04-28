#include "CollisionSystem.hpp"
#include "Events.hpp"
#include "World.hpp"
#include <iostream>
#include <cmath>




void CollisionSystem::update(MapSystem& map, double dt){
    auto& entities = getEntities();
    for(auto entity : entities){
        auto& collisionComponent = entity.getComponent<CollisionComponent>();
        auto& collisionBox = collisionComponent.collisionBox;
        auto& offsetX = collisionComponent.offsetX;
        auto& offsetY = collisionComponent.offsetY;
        auto& transform = entity.getComponent<TransformComponent>().transform;
        collisionBox.left = transform.getPosition().x + offsetX;
        collisionBox.top  = transform.getPosition().y + offsetY;
        checkTileCollision(map,entity);
    }

    /**
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
    **/

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

void CollisionSystem::checkTileCollision(MapSystem& map, Entity& entity){
    auto& entityCollisionBox = entity.getComponent<CollisionComponent>().collisionBox;
    std::size_t j = (entityCollisionBox.left + (entityCollisionBox.width * 0.5))/ map.tileSize;
    std::size_t i = (entityCollisionBox.top + (entityCollisionBox.height * 0.5))/ map.tileSize;
    std::size_t i0 = i-1;
    std::size_t i1 = i+1;
    std::size_t j0 = j-1;
    std::size_t j1 = j+1;
    std::array<std::pair<std::size_t,std::size_t>,9> indicesToCheck = {{
            {i0,j0},
            {i0,j},
            {i0,j1},
            {i,j0},
            {i,j},
            {i,j1},
            {i1,j0},
            {i1,j},
            {i1,j1}
    }};

    for(auto& index : indicesToCheck){
        std::size_t mapSize  = map.size();
        if(index.first>=mapSize || index.second>=mapSize)
            return;
        if(map.isPassable(index))
            continue;

        auto& tile = map.getTile(index.first, index.second);
        auto& tileCollisionBox = tile.getComponent<TileComponent>().shape;
        if(entityCollisionBox.intersects(tileCollisionBox.getGlobalBounds())){
            float dx = (entityCollisionBox.left - tileCollisionBox.getPosition().x);
            float dy = (entityCollisionBox.top - tileCollisionBox.getPosition().y);
            float overlapWidth = tileCollisionBox.getSize().x - std::abs(dx) + 0.5;
            float overlapHeight = tileCollisionBox.getSize().y - std::abs(dy) + 0.5;
            sf::Vector2f dr;
            if(overlapWidth > overlapHeight){
                if(dy<0)
                    dr.y = -overlapHeight;
                else
                    dr.y = overlapHeight;
            }
            else {
                if(dx<0)
                    dr.x = -overlapWidth;
                else
                    dr.x = overlapWidth;
            }

            getWorld().messageHandler().emit<CollisionResolutionEvent>(dr, entity);

            /**
            if(!entity.hasComponent<PlayerComponent>() && entity.hasComponent<VelocityComponent>()){
                auto& velocity = entity.getComponent<VelocityComponent>().velocity;
                auto& direction = entity.getComponent<DirectionComponent>().direction;
                velocity *= -1.0f;
                if(std::abs(velocity.x)>std::abs(velocity.y)){
                    if(velocity.x < 0){
                        direction = DirectionComponent::Direction::WEST;
                    }
                    else {
                        direction = DirectionComponent::Direction::EAST;
                    }
                }
                else {
                    if(velocity.y < 0){
                        direction = DirectionComponent::Direction::NORTH;
                    }
                    else{
                        direction = DirectionComponent::Direction::SOUTH;
                    }
                }
                getWorld().messageHandler().emit<DirectionChangedEvent>(entity,direction);
            }
            **/
        }
    }
}

