#include "World.hpp"
#include <cassert>
#include <algorithm>

World::World(std::size_t entityPoolSize) :
    m_entityIDPool(entityPoolSize),
    m_entityAttributes(entityPoolSize)
{
}

World::World() :
    World(MAX_ENTITY)
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
        attribute.activated = true;
        /** Get the bitset of components this entity has **/
        auto componentTypeList = m_entityAttributes.componentStorage.getComponentTypeList(entity);

        for(auto& keyvalue : m_systems){
            auto sysindex = keyvalue.first;
            auto& system = keyvalue.second;
            /** This newly activated entity has components the system can work on,
             * add it to the system
             * **/
            if(system->getFilter().passFilter(componentTypeList)){
                /** If the entity is being matched against the system for the first time **/
                if(attribute.systems.size() <= sysindex || !attribute.systems[sysindex]){
                    system->addEntity(entity);

                    /** The systems attribute must match **/
                    if(attribute.systems.size() <= sysindex)
                        attribute.systems.resize(sysindex +1);
                    attribute.systems[sysindex] = true;
                }
            }

            /** The entity no longer matches the systems filter (maybe removed component
             *  and the corresponding system bitfield for this entity must be nulled
             *  & removed. */
            else if(attribute.systems.size() > sysindex && attribute.systems[sysindex]){
                system->removeEntity(entity);
                attribute.systems[sysindex] = false;
            }
        }
    }

    for(auto& entity: m_cache.deactivated){
        auto& attribute = m_entityAttributes.attributes[entity.getID().index];
        attribute.activated = false;

        for(auto& keyvalue : m_systems){
            auto sysindex = keyvalue.first;
            auto& system = keyvalue.second;
            /** Doesn't match this system **/
            if(attribute.systems.size() <= sysindex) continue;
            /** Matches, deactivate in the system **/
            if(attribute.systems[sysindex]){
                system->removeEntity(entity);
                attribute.systems[sysindex] = false;
            }
        }
    }

    /** A dead entity is to be removed entirely **/
    for(auto& entity: m_cache.killed){
        m_cache.alive.erase(std::remove(m_cache.alive.begin(), m_cache.alive.end(), entity), m_cache.alive.end());
        m_entityAttributes.componentStorage.removeAllComponents(entity);
    }

    /** Clear the temp cache **/
    m_cache.clearTemporaries();
}

void World::addSystem(BaseSystem& system, TypeID systemTypeID){
    assert(!system.m_world && "System already has a world...");
    /** Replace whatever system was already there with this ... **/
    m_systems[systemTypeID].reset(&system);
    system.m_world = this;
    system.initialize();
}
