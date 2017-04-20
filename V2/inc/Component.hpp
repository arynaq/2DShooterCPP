#pragma once

#include <type_traits>
#include <vector>
#include "ClassTypeId.hpp"


#define MAX_COMPONENTS 100



class Component {

    public:
        virtual ~Component() {}

};

/**
 * Disregard template overload resolution if T is not base of Component
 * instead of generating compile time error 
 *
 * */

template <class T, class = typename std::enable_if<std::is_base_of<Component,T>::value>>
using ComponentPtr = T*;

using ComponentArray = std::vector<Component*>;


/**
 * TypeID is just a typedef for std::size_t
 * What this function does is try to map the type T to a unique integer (staticially incremented everytime
 * a component is created) in the class ClassTypeId
 *
 * This allows for mapping a Component to an integer for bitsets
 *
 * */
template <class T>
TypeID ComponentTypeID(){
    return ClassTypeId<Component>::GetTypeID<T>();
}
