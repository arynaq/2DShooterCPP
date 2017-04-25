#include "AISystem.hpp"
#include <queue>
#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <unordered_map>

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

        std::priority_queue<Node,std::vector<Node>,decltype(cmp) > frontier(cmp);
        Node start{map.getOccupiedTile(entity), 0 };
        Node end{map.getOccupiedTile(entity.getComponent<AIComponent>().target), 0};
        frontier.push(start);

        auto& transformComponent = entity.getComponent<TransformComponent>().transform;
        std::cout<<transformComponent.getPosition().y<<std::endl;


        while(!frontier.empty()){
            auto current = frontier.top();
            auto& neighborTile = current.location.getComponent<TileComponent>();
            std::cout<<neighborTile.index.first<<","<<neighborTile.index.second<<std::endl;
            frontier.pop();
            if(end == current){
                std::cout<<"Found target!"<<std::endl;
                came_from[end] = current;
                break;
            }
            auto neighbors = map.getNeighboringTiles(current.location);
            for(auto& neighbor : neighbors){
                Node next{neighbor, 0};
                double new_cost = cost_so_far[current] + manhattan_distance(current, next);
                if(!cost_so_far.count(next) || new_cost < cost_so_far[next]){
                    cost_so_far[next] = new_cost;
                    next.cost = new_cost + manhattan_distance(end,next);
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
        path.push_back(start);
        for(auto& p : path){

            p.location.getComponent<TileComponent>().tagged = true;
        }
    }
}
