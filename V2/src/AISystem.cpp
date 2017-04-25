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


double AISystem::manhattan_distance(Node& start, Node& end){
    auto& startTile = start.location;
    auto& endTile = end.location;
    auto& endTileShape = endTile.getComponent<TileComponent>().shape;
    auto& startTileShape = startTile.getComponent<TileComponent>().shape;
    auto width = endTileShape.getSize().x;
    auto height = endTileShape.getSize().y;
    double dx = (1.0/width) * std::abs(endTileShape.getPosition().x - startTileShape.getPosition().x);
    double dy = (1.0/height) * std::abs(endTileShape.getPosition().y - startTileShape.getPosition().y);
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
        CostMap cost_so_far;
        PathMap came_from;

        std::priority_queue<Node,std::vector<Node>,decltype(cmp) > frontier(cmp);
        Node start{map.getOccupiedTile(entity), 0 };
        Node end{map.getOccupiedTile(entity.getComponent<AIComponent>().target), 0};
        return;
        frontier.push(start);

        auto& transformComponent = entity.getComponent<TransformComponent>().transform;
        std::cout<<"AI tracing for entity at: " << transformComponent.getPosition().x<<",";
        std::cout<<transformComponent.getPosition().y<<std::endl;


        while(!frontier.empty()){
            auto current = frontier.top();
            frontier.pop();
            if(end == current){
                std::cout<<"Found target!"<<std::endl;
                return;
            }
            auto neighbors = map.getNeighboringTiles(current.location);
            auto& currentTile = current.location.getComponent<TileComponent>();
            std::cout<<"Neighbors for current "<<currentTile.index.first<<","<<currentTile.index.second<<": ";
            std::cout<<std::endl;
            for(auto& neighbor : neighbors){
                auto& neighborTile = neighbor.getComponent<TileComponent>();
                std::cout<<neighborTile.index.first<<","<<neighborTile.index.second<<std::endl;
                Node next{neighbor, 0};
                double heuristic = manhattan_distance(next, end);
                if(!came_from.count(next)){
                    next.cost = heuristic;
                    frontier.push(next);
                    came_from[next] = current;
                }
                std::cout<<"Cost: " << next.cost << std::endl;
            }
        }


    }
}
