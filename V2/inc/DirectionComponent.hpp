#pragma once
#include "Component.hpp"

struct DirectionComponent : Component{
    enum Direction{
        NORTH = 0,
        SOUTH,
        WEST,
        EAST,
        UNDEFINED
    }direction;
};
