#include "AISystem.hpp"
#include <queue>
#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <unordered_map>
#include <algorithm>
#include "World.hpp"

/**
 * @TODO:
 * You need the list of nodes before the update runs...
 * Which means
 * a) Create a list of nodes for every single tile
 * b) Dont depend on the idea of node, keep maybe
 *    An unordered_map for each tile to show whether it has been visited
 *    http://web.mit.edu/eranki/www/tutorials/search/
 *http://stackoverflow.com/questions/6990168/a-star-algorithm
http://www.redblobgames.com/pathfinding/a-star/implementation.html
 *    */

using Node = AISystem::Node;
using NodeHash = AISystem::NodeHash;
using EntityHash = AISystem::EntityHash;
using CostMap =  std::unordered_map<Node, double, NodeHash>;
using PathMap =  std::unordered_map<Node, Node, NodeHash>;
using Path = std::vector<Node>;


double AISystem::manhattan_distance(Node& start, Node& end){
    auto& startIndex = start.location.getComponent<TileComponent>().index;
    auto& endIndex = end.location.getComponent<TileComponent>().index;
    double dy = std::abs(startIndex.first - endIndex.first);
    double dx = std::abs(startIndex.second - endIndex.second);
    return dx + dy;
}

double AISystem::custom_heurestic(Node& start, Node& end){
    auto& startIndex = start.location.getComponent<TileComponent>().index;
    auto& endIndex = end.location.getComponent<TileComponent>().index;
    int x = std::max(startIndex.first, endIndex.first);
    int y = std::max(startIndex.second, endIndex.second);
    int score = std::min(x,y);
    if(x == 0)
        score = y;
    if(y == 0) 
        score = x;
    if(score == 0)
        return score;
    return score + (double)std::max(x,y)/score;
}

double AISystem::euclidean_distance(Node& start, Node& end){
    auto& startIndex = start.location.getComponent<TileComponent>().index;
    auto& endIndex = end.location.getComponent<TileComponent>().index;
    double dy = (startIndex.first - endIndex.first)*(startIndex.first - endIndex.first);
    double dx = (startIndex.second - endIndex.second)*(startIndex.second - endIndex.second);
    return std::sqrt(dx+dy);
}
void AISystem::update(MapSystem& map, double dt){
    /** 
     * Smallest elements appear at top of the priority queue 
     * */
    auto cmp = [](const Node& left, const Node& right){
        return left > right;
    };
    auto& entities = getEntities();
    std::vector<Entity> visitedTiles;
    for(auto& entity : entities){

        map.refresh();
        CostMap cost_so_far;
        PathMap came_from;
        Path path;

        /** Priority queue, top is always least cost node **/
        std::priority_queue<Node,std::vector<Node>,decltype(cmp) > frontier(cmp);
        Node start{map.getOccupiedTile(entity), 0 };
        Node end{map.getOccupiedTile(entity.getComponent<AIComponent>().target), 0};
        frontier.push(start);



        while(!frontier.empty()){
            auto current = frontier.top();
            frontier.pop();
            if(end == current){
                came_from[end] = current;
                break;
            }
            auto neighbors = map.getNeighboringTiles(current.location);
            for(auto& neighbor : neighbors){
                Node next{neighbor, 0};
                double new_cost = cost_so_far[current] + 1;//manhattan_distance(current, next);
                if(!cost_so_far.count(next) || new_cost < cost_so_far[next]){
                    cost_so_far[next] = new_cost;
                    double h = 10*euclidean_distance(end,next);
                    next.cost = new_cost + h;
                    frontier.push(next);
                    came_from[next] = current;
                }
            }
        }

        Node n = end;
        while(n!=start){
            n = came_from[n];
            path.push_back(n);
        }
        for(auto& p : path){
            p.location.getComponent<TileComponent>().tagged = true;
        }

        using Direction = DirectionComponent::Direction;
        if(entity.hasComponent<DirectionComponent>() && path.size()>=2){
            auto& startTile = path[path.size()-1].location.getComponent<TileComponent>();
            auto& nextTile = path[path.size()-2].location.getComponent<TileComponent>();
            auto& entityBox = entity.getComponent<CollisionComponent>().collisionBox;
            auto startBox = startTile.shape.getGlobalBounds();
            int deltaJIndex = nextTile.index.second - startTile.index.second;
            int deltaIIndex = nextTile.index.first - startTile.index.first;
            auto direction = Direction::UNDEFINED;

            if(!centeredMap.count(entity.getID().index)){
                float entityCenterX = entityBox.left + entityBox.width/2;
                float entityCenterY = entityBox.top + entityBox.height/2;
                float startCenterX = startBox.left + startBox.width/2;
                float startCenterY = startBox.top  + startBox.height/2;
                float dx = entityCenterX  - startCenterX;
                float dy = entityCenterY  - startCenterY;
                entity.getComponent<TransformComponent>().transform.move(-dx,-dy);
                centeredMap[entity.getID().index] = true;
            }
            if(isCentered(startBox,entityBox)){
                if(deltaIIndex < 0 )
                    direction = Direction::NORTH;
                else if(deltaIIndex > 0)
                    direction = Direction::SOUTH;
                else if(deltaJIndex < 0)
                    direction = Direction::WEST;
                else if(deltaJIndex > 0)
                    direction = Direction::EAST;
                getWorld().messageHandler().emit<DirectionChangedEvent>(entity, direction);
            }

        }
    }
}


bool AISystem::isCentered(sf::FloatRect& tile, sf::FloatRect& entity){
    return tile.contains(entity.left, entity.top)
        && tile.contains(entity.left+entity.width, entity.top)
        && tile.contains(entity.left,entity.top+entity.height)
        && tile.contains(entity.left+entity.width, entity.height+entity.top);
}
