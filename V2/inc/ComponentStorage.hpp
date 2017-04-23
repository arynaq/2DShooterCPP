#pragma once

#include "Component.hpp"
#include "Entity.hpp"
#include "ComponentTypeList.hpp"
#include <array>
#include <memory>

/**
 *
 * Storage class for every component in the world
 * */

class ComponentStorage {
    public:
        explicit ComponentStorage(std::size_t entityAmmount);

        ComponentStorage(const ComponentStorage&) = delete;
        ComponentStorage(ComponentStorage&&) = delete;
        ComponentStorage& operator=(const ComponentStorage&) = delete;
        ComponentStorage& operator=(ComponentStorage&&) = delete;


        /**
         * Adds a component to the given entity with the given componenttypeID
         * */
        void addComponent(Entity& e, Component* c, TypeID componentTypeID);
        void removeComponent(Entity& e, TypeID componentTypeID);
        void removeAllComponents(Entity& e);
        bool hasComponent(const Entity& e, TypeID componentTypeID);
        Component& getComponent(const Entity& entity, TypeID componentTypeID) const;
        ComponentArray getComponent(const Entity& entity) const;
        ComponentTypeList getComponentTypeList(const Entity& entity) const;


    private:
        /**
         * This class is the owner of all components
         * Index of array correponds to TypeID
         * */
        using ImplementationArray = std::array<std::unique_ptr<Component>, MAX_COMPONENTS>;

        /**
         * Date encapsulator
         * */
        struct EntityComponents {
            EntityComponents() = default;
            /** The actual components an entity has **/
            ImplementationArray components;
            /** Bitset of what components an entity has **/
            ComponentTypeList componentTypeList;
        };


        /** All the components for every entity, where the index of
         * the vector corresponds to the index part of a Entity::ID
         * */
        std::vector<EntityComponents> m_componentEntries;

        ImplementationArray& getComponentsImplemenation(const Entity& e);
};
