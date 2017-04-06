#pragma once

#include "Entity.hpp"
#include "Filter.hpp"

class BaseSystem {
    public:
        BaseSystem(const Filter& filter);
        virtual ~BaseSystem() = 0;

        const Filter& getFilter() const;
        World& getWorld() const;
        const std::vector<Entity>& getEntities() const;

    private:
        virtual void initialize(){}
        virtual void onEntityAdded(Entity& entity){}
        virtual void onEntityRemoved(Entity& entity){}

        void addEntity(Entity& entity);
        void removeEntity(Entity& entity);
        void setWorld(World& world);

        World* m_world;
        Filter m_filter;
        std::vector<Entity> m_entities;


        friend class World;
};
