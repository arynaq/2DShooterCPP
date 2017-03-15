#include "Entity.hpp"

Entity::Entity(World& world, Entity::ID id) : m_id(id),m_world(&world){
}

const Entity::ID& Entity::getID() const{
    return m_id;
}

World& Entity::getWorld() const{
    return *m_world;
}


void Entity::addComponent(Component* component, TypeId componentTypeId){
    

}
