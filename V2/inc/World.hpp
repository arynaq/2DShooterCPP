#pragma once
#include "Entity.hpp"
#include "Component.hpp"
#include "EntityIDPool.hpp"
#include "ComponentStorage.hpp"
#include "System.hpp"
#include <memory>
#include <unordered_map>
#include <iostream>
#include "MessageHandler.hpp"

class World {
    public:
        using EntityArray = std::vector<Entity>;
        using SystemArray = std::unordered_map<TypeID, std::unique_ptr<BaseSystem>>;

        World();
        /**
         * Initialize the world with a starting number of entities ready for use
         * **/
        explicit World(std::size_t entityPoolSize);
        /**
         * A world must be explicitly constructed, no copying allowed
         * */
        World(const World&) = delete;
        World(World&&) = delete;
        World& operator=(const World&) = delete;
        World& operator=(World&&) = delete;



        /**
         * Creates and returns a new entity for use
         * */
        Entity createEntity();
        /**
         * Creates a list of entities for use
         * */
        EntityArray createEntities(std::size_t ammount);


        /**
         * Kills the given entity
         * */
        void killEntity(Entity& entity);
        void activateEntity(Entity& entity);
        void deactivateEntity(Entity& entity);


        bool isValid(const Entity& e) const;

        /** 
         * Responsible for attaching entities to their corresponding system
         * Responsible for moving entities between the different caches
         * Responsible for cleaning entities from systems once they are dead
         *
         *
         * Must be called every update of the game
         * @Todo: Threadsafe
         * */

        void refresh();


        template <typename T, typename... Args>
        T& addSystem(Args&&... args);

        template <class RequireList, class ExcludeList = Excludes<>>
        EntityArray getEntities();

        MessageHandler& messageHandler();

    private:
        friend class Entity;
        EntityIDPool m_entityIDPool;
        SystemArray m_systems;
        MessageHandler m_messageHandler;

        struct EntityAttributes {
            struct Attribute {
                /**
                 * Whether an entity is activated **/
                bool activated;
                /**
                 * Whether a given system knows of the entities existence **/
                std::vector<bool> systems;
            };

            explicit EntityAttributes(std::size_t ammountOfEntities) :
                componentStorage(ammountOfEntities),
                attributes(ammountOfEntities)
            {
            }


            ComponentStorage componentStorage;
            /** Storage of attributes for each entity **/

            std::vector<Attribute> attributes;
        }
        m_entityAttributes;

        struct cache {
            EntityArray alive;
            EntityArray killed;
            EntityArray activated;
            EntityArray deactivated;

            void clear(){
                alive.clear();
                killed.clear();
                activated.clear();
                deactivated.clear();
            }

            void clearTemporaries(){
                killed.clear();
                activated.clear();
                deactivated.clear();
            }
        } m_cache;

        void addSystem(BaseSystem* system, TypeID systemTypeId);
        EntityArray getEntities(Filter& filter);
};


template <typename T, typename... Args>
T& World::addSystem(Args&&...args){
    auto* system = new T(std::forward<Args>(args)...);
    addSystem(system, SystemTypeId<T>());
    return static_cast<T&>(*m_systems[SystemTypeId<T>()].get());
}

template <class RequireList, class ExcludeList> //= Excludes<>>
World::EntityArray World::getEntities(){
    Filter f = MakeFilter<RequireList,ExcludeList>();
    return getEntities(f);
}

