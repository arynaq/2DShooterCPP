#include "World.hpp"
#include <cassert>

World::World(std::size_t entityPoolSize) :
    m_entityIDPool(entityPoolSize),
    m_entityAttributes(entityPoolSize)
{
}




Entity World::createEntity(){
    m_cache.alive.emplace_back(*this, m_entityIDPool.create());
    return m_cache.alive.back();
}


void World::activateEntity(Entity& entity){
    m_cache.activated.push_back(entity);
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

void World::refresh(){
    /** Newly activate entities
     *
     * */
    for(auto& entity : m_cache.activated){
        /** Get the attributes of this entity within this world **/
        auto& attribute  = m_entityAttributes.attributes[entity.getID().index];
        auto& 
        attribute.activiated = true;

        for(auto& system : m_systems){
        }
    }
}

void World::addSystem(BaseSystem& system, TypeID systemTypeID){
    assert(!system.m_world && "System already has a world...");
    /** Replace whatever system was already there with this ... **/
    m_systems[systemTypeID].reset(&system);
    system.m_world = this;
    system.initialize();
}
