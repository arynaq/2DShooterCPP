#pragma once
#include <Entity.hpp>
#include <vector>

class World {
    public:
        Entity createEntity();


    private:
        static ID counter = 0;
        std::vector<ID> entities;

        struct EntityAttributes {
            struct Attribute{
                bool activated;
                std::vector<bool> systems;
            };


            EntityComponentStorage
            std::vector<Attribute> attributes;
        }
        m_entityAttributes;



};

