#pragma once
#include "System.hpp"
#include "Components.hpp"
#include "Events.hpp"
#include "MapSystem.hpp"
#include <utility>
#include <unordered_map>

struct AISystem : System<Requires<AIComponent>> {
    void update(MapSystem& map, double dt);


    struct Node{
        Entity location;
        double cost;

        bool operator<(const Node& other) const {
            return cost < other.cost;
        }

        bool operator>(const Node& other) const{
            return other.operator<(*this);
        }

        bool operator==(const Node& other) const {
            int x = location.getComponent<TileComponent>().shape.getPosition().x;
            int y = location.getComponent<TileComponent>().shape.getPosition().y;
            int ox = other.location.getComponent<TileComponent>().shape.getPosition().x;
            int oy = other.location.getComponent<TileComponent>().shape.getPosition().y;
            return x==ox && y == oy;
        }
    };


    struct EntityHash {
        std::size_t operator()(const Entity& entity) const{
            return (std::hash<std::size_t>()(entity.getID().index));
        }
    };

    struct NodeHash {
        std::size_t operator()(const Node& node) const{
            return ((EntityHash()(node.location))
                ^ (std::hash<double>()(node.cost))<<1)>>1;
        }
    };

    private:
        double manhattan_distance(Node& start, Node& end);
};
