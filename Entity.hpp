#pragma once
#include <cstdint>
#include "Component.hpp"
#include "ClassTypeId.hpp"
#include <type_traits>

#define ENTITY_ID_INDEX_BIT_COUNT 20
#define ENTITY_ID_COUNT_BIT_COUNT 12

class World;
class Entity{
    public:
        struct ID{
            typedef std::uint32_t i32;
            ID() : index(0), count(0){
            }

            inline
                i32 value() const {
                    return (index << ENTITY_ID_INDEX_BIT_COUNT) | count;
                }

            i32 index : ENTITY_ID_INDEX_BIT_COUNT;
            i32 count : ENTITY_ID_COUNT_BIT_COUNT;
        };

        Entity(World& world, ID id);

        const ID& getID() const;
        World& getWorld() const;

        template<typename T, typename...Args>
        T& addComponent(Args&&... args);

    private:

        void addComponent(Component* component, TypeId componentTypeId);

        ID m_id;
        World* m_world;



};

template<typename T, typename...Args>
T& Entity::addComponent(Args&&... args){
    static_assert(std::is_base_of<Component,T>::value, "T ios not derived from Component.");
    auto component = new T{std::forward<Args>(args)...};
    addComponent(component, ComponentTypeId<T>());
    return *component;
}

