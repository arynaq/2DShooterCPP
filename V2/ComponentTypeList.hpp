#pragma once

#include <bitset>
#include "Component.hpp"

/**
 * A bitset where the index of the bitset corresponds to a given components TypeID
 * Which eamns that if the vlaue at index is 1: the componet type exists
 * 0: the component type does not exist
 * **/

using ComponentTypeList = std::bitset<MAX_COMPONENTS>;
