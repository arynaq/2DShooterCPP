#include "AISystem.hpp"
#include <queue>
#include <iostream>
#include <cmath>
#include <vector>
#include <functional>

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
                double dx = std::abs(currentTile.getPosition().x - neighborTile.getPosition().x);
                double dy = std::abs(currentTile.getPosition().y - neighborTile.getPosition().y);
                // manhattan cost
                double m_cost = dx + dy;
                double cost = current.f + m_cost;
                next->f = cost;
                frontier.push(next);
            }

            for(std::size_t i=0; i<frontier.size(); ++i){
                ANode* node = frontier.top();
                frontier.pop();
                std::cout<<"Cost: " << node->f<<std::endl;
            }
        }
    }
}
