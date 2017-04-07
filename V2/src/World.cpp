#include "World.hpp"

World::World(std::size_t entityPoolSize) :
    m_entityIDPool(entityPoolSize),
    m_entityAttributes(entityPoolSize)
{
}




Entity World::createEntity(){
    m_cache.alive.emplace_back(*this, m_entityIDPool.create());
    return m_cache.alive.back();
}

void World::deactivateEntity(Entity& entity){
    m_cache.deactivated.push_back(entity);
}

void World::killEntity(Entity& entity){
    deactivateEntity(entity);
    m_cache.killed.push_back(entity);
}

bool World::isValid(const Entity& e) const {
    return m_entityIDPool.isValid(e.getID());
}

