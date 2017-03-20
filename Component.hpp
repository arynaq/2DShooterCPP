#pragma once
#include <vector>
#include <type_traits>
#include "ClassTypeId.hpp"

#define MAX_COMPONENTS 1000


class Component {
    public:
        virtual ~Component(){}
        virtual void reset();
};

template<class T, class = typename std::enable_if<std::is_base_of<Component,T>::value>::type>
using ComponentPtr = T*;

using ComponentArray = std::vector<Component*>;

template<class T>
TypeId ComponentTypeId(){
    return ClassTypeId<Component>::GetTypeId<T>();
}



