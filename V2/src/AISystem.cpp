#include "AISystem.hpp"
#include <queue>
#include <iostream>
#include <cmath>
#include <vector>
#include <functional>

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
void AISystem::update(MapSystem& map, double dt){
    auto& entities = getEntities();
    for(auto& entity : entities){
        auto cmp = [](ANode* left, ANode* right){
            return (*left)>(*right);
        };
        std::priority_queue<ANode*,std::vector<ANode*>,decltype(cmp) > frontier(cmp);
        auto neighbors = map.getNeighboringTiles(entity);
        ANode* start = new ANode{nullptr, map.getOccupiedTile(entity), 0, 0, 0};
        ANode* end   = new ANode{nullptr, map.getOccupiedTile(entity.getComponent<AIComponent>().target),0,0,0};

        frontier.push(start);
        while(!frontier.empty()){

            auto current = *(frontier.top());
        std::cout<<"Checking location: " << current.location.getComponent<TileComponent>().shape.getPosition().x;
        std::cout<<"," << current.location.getComponent<TileComponent>().shape.getPosition().y;
        std::cout<<" vs "<< end->location.getComponent<TileComponent>().shape.getPosition().x;
        std::cout<<","<< end->location.getComponent<TileComponent>().shape.getPosition().y<<std::endl;
            std::cout<<"Frontier size: " << frontier.size()<<std::endl;
            auto& currentTile = current.location.getComponent<TileComponent>().shape;
            if(*end == current){
                std::cout<<"Found target!"<<std::endl;
                break;
            }

            for(auto& neighbor : neighbors){
                ANode* next = new ANode{&current, neighbor, 0, 0, 0};
                auto& neighborTile  = neighbor.getComponent<TileComponent>().shape;
                double dx = std::abs(currentTile.getPosition().x - neighborTile.getPosition().x)*1.0/32;
                double dy = std::abs(currentTile.getPosition().y - neighborTile.getPosition().y)*1.0/32;
                // manhattan cost
                double m_cost = dx + dy;
                double newCost = current.f + m_cost;
                if(newCost < next.f){

                }
                next->f = cost;
                frontier.push(next);
            }
        }
    }
}
