#include "EntityComponentStorage.hpp"

void EntityComponentStorage::addComponent(Entity& entity, Component* component, TypeId componentTypeId){
    auto index = entity.getID().index;
    auto& componentDataForEntity = m_componentEntries[index];

    componentDataForEntity.components[componentTypeId].reset();
    componentDataForEntity.componentTypeList[componentTypeId] = true;
}

