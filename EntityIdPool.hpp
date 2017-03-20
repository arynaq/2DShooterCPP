#pragma once
#include "Entity.hpp"
#include <vector>

class EntityIdPool{
    public:
        explicit EntityIdPool(std::size_t poolSize);

        EntityIdPool(const EntityIdPool&) = delete;
        EntityIdPool(EntityIdPool&&) = delete;
        EntityIdPool& operator=(const EntityIdPool&) = delete;
        EntityIdPool& operator=(EntityIdPool&&) = delete;

        Entity::ID create();


        bool isValid(Entity::ID id) const;

    private:
        std::size_t m_defaultPoolSize;

        Entity::ID::i32 m_nextId;

        std::vector<Entity::ID> m_freeList;
        std::vector<Entity::ID::i32> m_counts;

};
