#include "ComponentStorage.hpp"
#include <cassert>


ComponentStorage::ComponentStorage(std::size_t entityAmmount) :
    m_componentEntries(entityAmmount)
{
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

