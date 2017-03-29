#pragma once
#include <cstdint>
#include "Component.hpp"

#define ENTITY_COUNTER_BITS 16

class World;
class Entity {

    public:
        struct ID {
            using u32 = std::uint32_t;
            u32 index : ENTITY_COUNTER_BITS;   // bitfield 16 bits for this variable
            u32 counter : ENTITY_COUNTER_BITS;

            ID(u32 index, u32 counter) :
                index(index), counter(counter)
            {
            }

            inline
            u32 value() const {
                return (counter << ENTITY_COUNTER_BITS  )| index;
            }
        };


        Entity(World& world, ID id);

        World& getWorld() const;


        ID& getID() const;


        template<typename T, typename...Args>
        T& addComponent(Args&&...args);


        template<typename T>
        void removeComponent();


        void removeAllComponents();


        template<typename T>
        T& getComponent() const;


        template<typename T>
        bool hasComponent() const;


        /**
         * Returns every component this entity has
         * ComponentArray is a typedef for std::vector<Component*>
         * **/
        ComponentArray getComponents() const;


    private:
        ID m_id;
        World* m_world;
};
