#include "BaseSystem.hpp"
#include <cassert>
#include <algorithm>

BaseSystem::BaseSystem(const Filter& filter) :
    m_world(nullptr),
    m_filter(filter)
{
}

BaseSystem::~BaseSystem(){}

const Filter& BaseSystem::getFilter() const {
    return m_filter;
}

World& BaseSystem::getWorld() const {
    assert(m_world && "World is null...");
    return  *m_world;
}

void BaseSystem::addEntity(Entity& entity){
    m_entities.push_back(entity);
    onEntityAdded(entity);
}

void BaseSystem::removeEntity(Entity& entity){
    m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());
    onEntityRemoved(entity);
}

