#include "BaseSystem.hpp"
#include <cassert>
#include <algorithm>


BaseSystem::BaseSystem(const Filter& filter):
    m_world(nullptr),
    m_filter(filter)
{
}

BaseSystem::~BaseSystem(){
}

const Filter& BaseSystem::getFilter() const{
    return m_filter;
}

const std::vector<Entity>& BaseSystem::getEntities() const{
    return m_entities;
}

World& BaseSystem::getWorld() const {
    assert(m_world != nullptr);
    return *m_world;
}

void BaseSystem::add(Entity& e){
    m_entities.push_back(e);
    onEntityAdded(e);
}

void BaseSystem::remove(Entity& e){
    m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), e), m_entities.end());
    onEntityRemoved(e);
}
