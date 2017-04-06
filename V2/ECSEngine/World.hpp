#pragma once
#include "Entity.hpp"
#include "Component.hpp"
#include "EntityIDPool.hpp"
#include <vector>
#include "ComponentStorage.hpp"

class World {
    public:
        using EntityArray = std::vector<Entity>;

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



        void deactivateEntity(Entity& entity);


        bool isValid(const Entity& e) const;


    private:
        friend class Entity;
        EntityIDPool m_entityIDPool;


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
};
