#pragma once
#include <cstdint>
#include "Component.hpp"

#define ENTITY_COUNTER_BITS 16
#define MAX_ENTITY 2000

class World;
class Entity {

    public:
        struct ID {
            using u32 = std::uint32_t;
            u32 index : ENTITY_COUNTER_BITS;   // bitfield 16 bits for this variable
            u32 counter : ENTITY_COUNTER_BITS;

            ID(u32 index, u32 counter) :
                index(index), counter(counter)
            {
            }

            ID() : ID(0,0) {}

            inline
            u32 value() const {
                return (counter << ENTITY_COUNTER_BITS  )| index;
            }
        };


        Entity();
        Entity(World& world, ID id);

        World& getWorld() const;


        const ID& getID() const;


        /**
         * Adds a new component T that is derived from Component,
         * looks up its typeid using ClassTypeID<Component>::GetTypeID<T>())
         * */
        template<typename T, typename...Args>
        T& addComponent(Args&&...args);


        template<typename T>
        void removeComponent();


        void removeAllComponents();


        template<typename T>
        T& getComponent() const;


        template<typename T>
        bool hasComponent() const;


        /**
         * Returns every component this entity has
         * ComponentArray is a typedef for std::vector<Component*>
         * **/
        ComponentArray getComponents() const;



        /**
         * Check if this entity is valid in its own world.
         *
         * Only way it can be valid is if the worlds entity storage created it
         * and it is also alive.
         * */
        bool isValid() const;
        
        bool operator==(const Entity& entity) const;
        bool operator!=(const Entity& entity) const {
            return !operator==(entity);
        }


        void activate();
        void deactivate();
        void kill();


    private:
        ID m_id;
        World* m_world;

        /** Private helper method for adding a component to this entity
         *  TypeID is a typedef for std::size_t and is unique identifier per 
         *  component type
         *  */
        void addComponent(Component* component, TypeID componentTypeID);
        void removeComponent(TypeID componentTypeID);
        Component& getComponent(TypeID componentTypeID) const;
};

template<typename T>
void assertComponentDerived(){
    static_assert(std::is_base_of<Component,T>(), "T is not derived from component...");
}


template<typename T, typename... Args>
T& Entity::addComponent(Args&&...args){
    assertComponentDerived<T>();
    auto component = new T{std::forward<Args>(args)...};
    addComponent(component, ComponentTypeID<T>());
    return *component;
}



template<typename T>
void Entity::removeComponent() {
    assertComponentDerived<T>();
    removeComponent(ComponentTypeID<T>());
}


/**
 * Returns a references to the component of type T that this entity has 
 * */
template<typename T>
T& Entity::getComponent() const {
    assertComponentDerived<T>();
    return static_cast<T&>(getComponent(ComponentTypeID<T>()));
}
