#include "MapSystem.hpp"
#include "World.hpp"
#include <iostream>
#include "Events.hpp"
#include <cmath>

void MapSystem::initialize(){
    for(int i=0; i<32; ++i){
        for(int j=0; j<32; ++j){
            std::cout<<map[i][j]<<std::endl;
            auto tile = getWorld().createEntity();
            auto& tileComponent = tile.addComponent<TileComponent>();
            if(map[i][j] == 1){
                tileComponent.shape.setFillColor(sf::Color::Black);
                tileComponent.shape.setOutlineThickness(1);
                tileComponent.shape.setOutlineColor(sf::Color::Red);
            }
            if(map[i][j] == 0){
                tileComponent.shape.setOutlineThickness(1);
                tileComponent.shape.setOutlineColor(sf::Color::Yellow);
                tileComponent.shape.setFillColor(sf::Color::Black);
            }
            tileComponent.shape.setPosition(j*32,i*32);
            tile.activate();
            tileMap[i][j] = tile;
        }
    }
}

bool MapSystem::checkTileCollision(Entity entity){
    if(!entity.hasComponent<CollisionComponent>())
        return true;

    sf::FloatRect entityCollisionBox = entity.getComponent<CollisionComponent>().collisionBox;
    std::size_t j = entityCollisionBox.left/ tileSize;
    std::size_t i = entityCollisionBox.top / tileSize;
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
        std::size_t mapSize = tileMap.size();
        if(index.first>=mapSize || index.second>=mapSize)
            return true;
        if(map[index.first][index.second] == 1)
            continue;

        auto& tileCollisionBox = tileMap[index.first][index.second].getComponent<TileComponent>().shape;
        if(entityCollisionBox.intersects(tileCollisionBox.getGlobalBounds())){
            float dx = (entityCollisionBox.left - tileCollisionBox.getPosition().x);
            float dy = (entityCollisionBox.top - tileCollisionBox.getPosition().y);
            float overlapWidth = entityCollisionBox.width - std::abs(dx) + 1;
            float overlapHeight = entityCollisionBox.height - std::abs(dy) + 1;
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
            auto& transform = entity.getComponent<TransformComponent>().transform;
            transform.move(dr);
            return true;
        }
    }
    return false;
}

bool MapSystem::doesCollide(std::pair<std::size_t,std::size_t>& index,  sf::FloatRect& collisionBox){
    std::size_t mapSize = tileMap.size();
    if(index.first>=mapSize || index.second>=mapSize)
        return true;

    if(map[index.first][index.second] == 1) return false;

    auto& tileCollisionBox = tileMap[index.first][index.second].getComponent<TileComponent>().shape;

    if(collisionBox.intersects(tileCollisionBox.getGlobalBounds())){
        float dx = tileCollisionBox.getPosition().x - collisionBox.left;
        float dy = tileCollisionBox.getPosition().y - collisionBox.top;
        std::cout<<"dx,dy: " << dx <<","<<dy<<std::endl;
        return true;
    }
    return false;
}
