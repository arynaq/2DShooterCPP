#include "EntityIDPool.hpp"

EntityIDPool::EntityIDPool(std::size_t poolSize) :
    m_nextID(0),
    m_counts(poolSize)
{
}



Entity::ID EntityIDPool::create(){
    Entity::ID id;

    /**
     * Return from free list if not emtpy
     * */
    if(!m_usable.empty()){
        id = m_usable.back();
        m_usable.pop_back();
    }
    /**
     * Else return a fresh entity, set and store its count
     * */
    else {
        id.index = m_nextID++;
        m_counts[id.index] = id.counter = 1;
    }

    return id;
}


/**
 * If the index of the entities id is larger than this pool,
 * was not created here.
 *
 * If the counter of the entities id does not match, was not created here
 * */

bool EntityIDPool::isValid(Entity::ID id) const {
    if(id.index >= m_counts.size())
        return false;
    return id.counter == m_counts[id.index] && id.counter > 0;
}


/**
 * Invalidates an entity by increasing its counter
 * Then adds the ID to the free pool
 * */

void EntityIDPool::remove(Entity::ID id){
    Entity::ID::u32& counter = m_counts[id.index];
    ++counter;
    m_usable.emplace_back(static_cast<Entity::ID::u32>(id.index), counter);
}
