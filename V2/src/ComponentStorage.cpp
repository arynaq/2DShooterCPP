#include "ComponentStorage.hpp"
#include <cassert>


ComponentStorage::ComponentStorage(std::size_t entityAmmount) :
    m_componentEntries(entityAmmount)
{
}


ComponentTypeList ComponentStorage::getComponentTypeList(const Entity& entity) const {
    Entity::ID::u32 index = entity.getID().index;
    return m_componentEntries[index].componentTypeList;
}

Component& ComponentStorage::getComponent(const Entity& entity, TypeID componentTypeID) const {
    Entity::ID::u32 index = entity.getID().index;
    return *(m_componentEntries[index].components)[componentTypeID];
}

void ComponentStorage::addComponent(Entity& e, Component* c, TypeID componentTypeID) {
     assert(e.isValid() && "Invalid entity cannot have components added to it ");

    Entity::ID::u32 index = e.getID().index;
    EntityComponents& entityData =  m_componentEntries[index];

    /** std::unique_ptr.reset  -> replace the currently owned component
     * at index with the new component
     * */
    entityData.components[componentTypeID].reset(c);
    /** 
     * Validate the component type at the given index 
     * */
    entityData.componentTypeList[componentTypeID] = true;
}

bool ComponentStorage::hasComponent(const Entity& e, TypeID componentTypeID){
    Entity::ID::u32 index = e.getID().index;
    EntityComponents& entityData = m_componentEntries[index];
    return entityData.componentTypeList[componentTypeID];
}


void ComponentStorage::removeComponent(Entity& entity, TypeID componentTypeID){
    assert(entity.isValid() && "Invalid entity cannot have components added to it ");

    Entity::ID::u32 index = entity.getID().index;
    EntityComponents& entityData = m_componentEntries[index];

    /** Reset the given component with nullptr **/
    entityData.components[componentTypeID].reset();
    /* Invalidate the component for this given entity 
     * */
    entityData.componentTypeList[componentTypeID] = false;
}

void ComponentStorage::removeAllComponents(Entity& entity){
    auto index = entity.getID().index;
    auto& componentDataEntries = m_componentEntries[index];
    
    for(auto& component : componentDataEntries.components){
        component.reset();
    }
    componentDataEntries.componentTypeList.reset();
}

