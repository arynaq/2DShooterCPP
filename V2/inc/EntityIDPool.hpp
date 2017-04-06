#pragma once
#include "Entity.hpp"
#include <vector>

class EntityIDPool{
    public:
        explicit EntityIDPool(std::size_t poolSize);
        
        EntityIDPool(const EntityIDPool&) = delete;
        EntityIDPool(EntityIDPool&&) = delete;
        EntityIDPool& operator=(const EntityIDPool&) = delete;
        EntityIDPool& operator=(EntityIDPool&&) = delete;


        /**
         * Creates and returns an ID toe a new entity
         * */
        Entity::ID create();


        /**
         * Removes the given entity
         * **/
        void remove(Entity::ID id);


        bool isValid(Entity::ID id) const;


    private:
        std::size_t m_defaultPoolSize;


        Entity::ID::u32 m_nextID;


        /**
         * List of entity ids that are free to use
         * */
        std::vector<Entity::ID>  m_usable;


        /**
         * Entities that are within the pool
         * */
        std::vector<Entity::ID::u32> m_counts;

};
