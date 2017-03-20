#include "World.hpp"


bool World::isValid(const Entity& e) const{
    return m_entityIdPool.isValid(e.getID());
}
