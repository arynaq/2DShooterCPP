#include "Entity.hpp"
#include <cassert>
#include "World.hpp"


Entity::Entity(World& world, ID id) :
    m_id{id},
    m_world{&world}
{
}

World& Entity::getWorld() const{
    assert(m_world && "Entity world is null!");
    return *m_world;
}

const Entity::ID& Entity::getID() const {
    return m_id;
}

void Entity::addComponent(Component* component, TypeID componentTypeID){
    getWorld().m_entityAttributes.componentStorage.addComponent(*this, component, componentTypeID);
}

void Entity::removeComponent(TypeID componentTypeID){
    getWorld().m_entityAttributes.componentStorage.removeComponent(*this, componentTypeID);
}

void Entity::removeAllComponents(){

}

bool Entity::isValid() const {
    return getWorld().isValid(*this);
}


bool Entity::operator==(const Entity& entity) const {
    return m_id.value() == entity.m_id.value() && m_world == entity.m_world;
}
