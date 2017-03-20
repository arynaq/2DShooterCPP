#include "Entity.hpp"
#include "World.hpp"

Entity::Entity(World& world, Entity::ID id) : m_id(id),m_world(&world){
}

const Entity::ID& Entity::getID() const{
    return m_id;
}

World& Entity::getWorld() const{
    return *m_world;
}

bool Entity::isValid() const {
    if(m_world == nullptr) return false;
    
    return getWorld().isValid(*this);
}


void Entity::addComponent(Component* component, TypeId componentTypeId){
    getWorld().m_entityAttributes.componentStorage.addComponent(*this,component,componentTypeId);
}

bool Entity::operator==(const Entity& other) const {
    return m_id.value() == other.m_id.value() && m_world == other.m_world;
}
