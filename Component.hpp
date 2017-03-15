#pragma once
#include <vector>
#include <type_traits>
#include "ClassTypeId.hpp"


class Component {
    public:

        virtual ~Component(){}
};

template<class T, class = typename std::enable_if<std::is_base_of<Component,T>::value>::type>
using ComponentPtr = T*;

using ComponentArray = std::vector<Component*>;

template<class T>
TypeId ComponentTypeId(){
    return ClassTypeId<Component>::GetTypeId<T>();
}



