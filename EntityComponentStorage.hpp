#pragma once

#include "ClassTypeId.hpp"
#include <array>
#include "Entity.hpp"
#include <memory>
#include "Component.hpp"
#include "ComponentTypeList.hpp"
#include <vector>


class EntityComponentStorage {

    public:
        explicit EntityComponentStorage(std::size_t entityAmmount);


        EntityComponentStorage(const EntityComponentStorage&) = delete;
        EntityComponentStorage(EntityComponentStorage&) = delete;
        EntityComponentStorage& operator=(const EntityComponentStorage&) = delete;
        EntityComponentStorage& operator=(EntityComponentStorage&) = delete;


        void addComponent(Entity& entity, Component* component, TypeId componentTypeId);
        Component& getComponent(const Entity& entity, TypeId componentTypeId) const;


    private:
        using ComponentArray = std::array<std::unique_ptr<Component>, MAX_ENTITY_COUNT>;


        struct EntityComponents {
            EntityComponents() = default;


            EntityComponents(EntityComponents&& e):
                components(std::move(e.components)),
                componentTypeList(std::move(e.componentTypeList))
            {
            }

            ComponentArray components;
            ComponentTypeList componentTypeList;
        };


        std::vector<EntityComponents> m_componentEntries;

};
