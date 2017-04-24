#pragma once
#include "System.hpp"
#include "Components.hpp"
#include "Events.hpp"
#include "MapSystem.hpp"

struct AISystem : System<Requires<AIComponent>> {
    void update(MapSystem& map, double dt);

    struct ANode{
        ANode* parent;
        Entity location;
        double f,g,h;

        bool operator<(const ANode& other) const {
            return f < other.f;
        }

        bool operator>(const ANode& other) const {
            return other.operator<(*this);
        }

        bool operator==(const ANode& other) const{
            int x = location.getComponent<TileComponent>().shape.getPosition().x;
            int y = location.getComponent<TileComponent>().shape.getPosition().y;
            int ox = other.location.getComponent<TileComponent>().shape.getPosition().x;
            int oy = other.location.getComponent<TileComponent>().shape.getPosition().y;
            return x==ox && y == oy;
        }

    };
};
