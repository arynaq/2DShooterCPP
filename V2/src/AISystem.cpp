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
    std::cout<<"is,js"<<startIndex.first<<","<<startIndex.second<<std::endl;
    std::cout<<"ie,je"<<endIndex.first<<","<<endIndex.second<<std::endl;
    std::cout<<"dx,dy: " << dx <<","<<dy<<std::endl;
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
                //if(next == current) continue;
                double new_cost = cost_so_far[current] + 1;//manhattan_distance(current, next);
                if(!cost_so_far.count(next) || new_cost < cost_so_far[next]){
                    cost_so_far[next] = new_cost;
                    double h = 10*euclidean_distance(end,next);
                    next.cost = new_cost + h;
                    frontier.push(next);
                    came_from[next] = current;

                }
                /**
                  Node next{neighbor, 0};
                  double heuristic = manhattan_distance(next, end);
                  if(!came_from.count(next)){
                  next.cost = heuristic;
                  frontier.push(next);
                  came_from[next] = current;
                  }
                 **/
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
            auto& nextTile = path[path.size()-2].location.getComponent<TileComponent>();
            auto& startTile = path[path.size()-1].location.getComponent<TileComponent>();
            auto& entityBox = entity.getComponent<CollisionComponent>().collisionBox;
            auto  startBox = startTile.shape.getGlobalBounds();
            int deltaJIndex = nextTile.index.second - startTile.index.second;
            int deltaIIndex = nextTile.index.first - startTile.index.first;
            int directionX = 0;
            int directionY = 0;

            Direction d = Direction::UNDEFINED;
            if(deltaIIndex < 0){
                d = Direction::NORTH;
                directionY = -1;
            }
            else if(deltaIIndex > 0){
                d = Direction::SOUTH;
                directionY = 1;
            }
            else if(deltaJIndex < 0){
                d = Direction::WEST;
                directionX = -1;
            }
            else if(deltaJIndex > 0){
                d = Direction::EAST;
                directionX = 1;
            }
            sf::FloatRect next(entity.getComponent<CollisionComponent>().collisionBox);
            next.top += directionY*next.height;
            next.left += directionX*next.height;
            if(!map.isPassable(next)){
                if(d == Direction::EAST){
                    if(entityBox.top < startBox.top) 
                        d = Direction::SOUTH;
                    else 
                        d = Direction::NORTH
                }
                else if(d == DIRECTION::WEST){
                    if(entityBox.top < startBox.top)
                }

            }
            getWorld().messageHandler().emit<DirectionChangedEvent>(entity, d);
        }
    }
}
