#include "MapSystem.hpp"
#include "World.hpp"
#include <iostream>
#include "Events.hpp"

void MapSystem::initialize(){
    for(int i=0; i<32; ++i){
        for(int j=0; j<32; ++j){
            std::cout<<map[i][j]<<std::endl;
            auto tile = getWorld().createEntity();
            auto& tileComponent = tile.addComponent<TileComponent>();
            if(map[i][j] == 1){
                tileComponent.shape.setFillColor(sf::Color::Red);
                // auto& collisionComponent = tile.addComponent<CollisionComponent>();
                // collisionComponent.collisionBox.left = (j*32) + 1;
                // collisionComponent.collisionBox.top  = (i*32) + 1;
                // collisionComponent.collisionBox.width = 31;
                // collisionComponent.collisionBox.height = 31;
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

void MapSystem::checkTileCollision(Entity entity){
    auto& entityCollisionBox = entity.getComponent<CollisionComponent>().collisionBox;
    std::size_t j = entityCollisionBox.left / tileSize;
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
        if(doesCollide(index, entityCollisionBox)){
            auto& messageHandler = getWorld().messageHandler();
            messageHandler.emit<TileCollisionEvent>(entity, tileMap[index.first][index.second]);
        }
    }
}

bool MapSystem::doesCollide(std::pair<std::size_t,std::size_t>& index,  sf::FloatRect& collisionBox){
    std::cout<<"Requested check for i,j: " <<index.first<<","<<index.second;
    std::cout<<" vs: " <<collisionBox.left<<","<<collisionBox.top;
    std::cout<<","<<collisionBox.width<<","<<collisionBox.height<<std::endl;
    std::size_t mapSize = tileMap.size();
    if(index.first<0 || index.first>mapSize || index.second<0 || index.second>mapSize)
        return true;

    if(map[index.first][index.second] == 1) return false;
    return collisionBox.intersects(tileMap[index.first][index.second].getComponent<TileComponent>().shape.getGlobalBounds());
}
