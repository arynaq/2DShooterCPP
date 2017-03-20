#pragma once
#include "Entity.hpp"
#include <vector>
#include "EntityComponentStorage.hpp"
#include "EntityIdPool.hpp"

class World {
    public:
        using EntityArray = std::vector<Entity>;
        Entity createEntity();

        bool isValid(const Entity& e) const;


    private:
        struct EntityAttributes {
            struct Attribute{
                bool activated;
                std::vector<bool> systems;
            };


            EntityComponentStorage componentStorage;
            std::vector<Attribute> attributes;
        }
        m_entityAttributes;

        EntityIdPool m_entityIdPool;

    friend class Entity;

};

