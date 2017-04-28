#include "MapSystem.hpp"
#include "World.hpp"
#include <iostream>
#include "Events.hpp"
#include <cmath>

void MapSystem::initialize(){
    for(int i=0; i<32; ++i){
        for(int j=0; j<32; ++j){
            auto tile = getWorld().createEntity();
            auto& tileComponent = tile.addComponent<TileComponent>();
            if(map[i][j] == 1){
                tileComponent.shape.setFillColor(sf::Color::Transparent);
                tileComponent.passable = true;
            }
            if(map[i][j] == 0){
                tileComponent.shape.setOutlineThickness(1);
                tileComponent.shape.setOutlineColor(sf::Color::Yellow);
                tileComponent.shape.setFillColor(sf::Color::Black);
            }
            tileComponent.shape.setPosition(j*32,i*32);
            tileComponent.index.first = i;
            tileComponent.index.second = j;
            tile.activate();
            tileMap[i][j] = tile;

        }
    }
}

int MapSystem::size() const {
    return tileMap.size();
}

bool MapSystem::isPassable(Index& index) const{
    if(index.first >= tileMap.size() || index.second >= tileMap.size())
        return false;
    if(map[index.first][index.second] == 1)
        return true;
    return false;
}

void MapSystem::refresh(){
    for(std::size_t i=0; i<32; ++i){
        for(std::size_t j=0; j<32; ++j){
            tileMap[i][j].getComponent<TileComponent>().tagged = false;
        }
    }
}

Entity MapSystem::getOccupiedTile(const Entity& e){
    auto entityCollisionBox = e.getComponent<CollisionComponent>().collisionBox;
    std::size_t j = (entityCollisionBox.left + (entityCollisionBox.width * 0.5))/ tileSize;
    std::size_t i = (entityCollisionBox.top + (entityCollisionBox.height * 0.5))/ tileSize;
    assert(i<tileMap.size() && j<tileMap.size() && "Entity is outside map..");
    return tileMap[i][j];
}

const Entity& MapSystem::getTile(int i, int j){
    return tileMap[i][j];
}

std::vector<Entity> MapSystem::getNeighboringTiles(const Entity& e){
    std::vector<Entity> neighbors;
    neighbors.reserve(8);
    if(e.hasComponent<CollisionComponent>()){
        auto entityCollisionBox = e.getComponent<CollisionComponent>().collisionBox;
        std::size_t j = (entityCollisionBox.left + (entityCollisionBox.width * 0.5))/ tileSize;
        std::size_t i = (entityCollisionBox.top + (entityCollisionBox.height * 0.5))/ tileSize;
        std::size_t i0 = i-1;
        std::size_t i1 = i+1;
        std::size_t j0 = j-1;
        std::size_t j1 = j+1;
        std::array<std::pair<std::size_t,std::size_t>,9> indicesToCheck = {{
              {i0,j},
              {i,j0},
              {i,j1},
              {i1,j}
/**
            {i0,j0},
                {i0,j},
                {i0,j1},
                {i,j0},
                {i,j},
                {i,j1},
                {i1,j0},
                {i1,j},
                {i1,j1}
                **/
        }};

        for(auto& index : indicesToCheck){
            if(index.first >=tileMap.size() || index.second>=tileMap.size())
                continue;
            if(map[index.first][index.second] == 0)
                continue;
            neighbors.push_back(tileMap[index.first][index.second]);

        }
    }

    else if(e.hasComponent<TileComponent>()){
        std::size_t i = e.getComponent<TileComponent>().index.first;
        std::size_t j = e.getComponent<TileComponent>().index.second;
        std::size_t i0 = i-1;
        std::size_t i1 = i+1;
        std::size_t j0 = j-1;
        std::size_t j1 = j+1;
        std::array<std::pair<std::size_t,std::size_t>,9> indicesToCheck = {{
              {i0,j},
              {i,j0},
              {i,j1},
              {i1,j}
        }};

        for(auto& index : indicesToCheck){
            if(index.first >=tileMap.size() || index.second>=tileMap.size())
                continue;
            if(map[index.first][index.second] == 0)
                continue;
            neighbors.push_back(tileMap[index.first][index.second]);

        }
    }
    return neighbors;
}

bool MapSystem::checkTileCollision(Entity entity){
    if(!entity.hasComponent<CollisionComponent>())
        return true;

    sf::FloatRect entityCollisionBox = entity.getComponent<CollisionComponent>().collisionBox;
    std::size_t j = (entityCollisionBox.left + (entityCollisionBox.width * 0.5))/ tileSize;
    std::size_t i = (entityCollisionBox.top + (entityCollisionBox.height * 0.5))/ tileSize;
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
            float overlapWidth = tileCollisionBox.getSize().x - std::abs(dx) + 1;
            float overlapHeight = tileCollisionBox.getSize().y - std::abs(dy) + 1;
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
            if(!entity.hasComponent<PlayerComponent>()){
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
            return true;
        }
    }
    return false;
}

bool MapSystem::isPassable(sf::FloatRect& rect) const {
    Index topLeft(rect.top/tileSize, rect.left/tileSize);
    Index topRight(rect.top/tileSize, (rect.left + rect.width)/tileSize);
    Index bottomLeft((rect.top+rect.height)/tileSize, rect.left/tileSize);
    Index bottomRight((rect.top+rect.height)/tileSize, (rect.left+rect.width)/tileSize);

    bool pass = isPassable(topLeft) && isPassable(topRight)
        && isPassable(bottomLeft) && isPassable(bottomRight);

    return pass;
}

