#include "EntityIdPool.hpp"

EntityIdPool::EntityIdPool(std::size_t poolSize):
    m_defaultPoolSize(poolSize),
    m_nextId(0),
    m_counts(poolSize)
{
}

Entity::ID EntityIdPool::create(){
    Entity::ID id;
    
    if(!m_freeList.empty()){
        id = m_freeList.back();
        m_freeList.pop_back();
    }

    else {
        id.index = m_nextId++;
        m_counts[id.index] = id.count = 1;
    }

    return id;
}

bool EntityIdPool::isValid(Entity::ID id) const {
    if(id.index >= m_counts.size()){
        return false;
    }
    return (id.count == m_counts[id.index]) && (id.count > 0);
}
