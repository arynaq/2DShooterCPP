#pragma once

#include "Entity.hpp"

struct CollisionEvent{

    Entity e1;
    Entity e2;

    CollisionEvent(Entity left, Entity right) :
        e1(left), e2(right){}
};
