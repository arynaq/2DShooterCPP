#pragma once
#include <cstdint>
#include "Component.hpp"
#include "ClassTypeId.hpp"
#include <type_traits>

#define ENTITY_ID_INDEX_BIT_COUNT 20
#define ENTITY_ID_COUNT_BIT_COUNT 12
#define MAX_ENTITY_COUNT 1000

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


        Entity(const Entity&) = default;
        Entity(Entity&&) = default;
        Entity& operator=(const Entity&) = default;
        Entity& operator=(Entity&&) = default;
        
        const ID& getID() const;
        World& getWorld() const;

        template<typename T, typename...Args>
        T& addComponent(Args&&... args);

        bool isValid() const;

        bool operator==(const Entity& other) const;
        bool operator!=(const Entity& other) const {
            return !operator==(other);
        }

    private:

        void addComponent(Component* component, TypeId componentTypeId);

        ID m_id;
        World* m_world;



};

template<typename T, typename...Args>
T& Entity::addComponent(Args&&... args){
    static_assert(std::is_base_of<Component,T>::value, "T is not derived from Component.");
    auto component = new T{std::forward<Args>(args)...};
    addComponent(component, ComponentTypeId<T>());
    return *component;
}

