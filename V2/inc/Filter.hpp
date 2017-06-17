#pragma once

#include "ComponentTypeList.hpp"
#include <iostream>

template <class... Args>
struct TypeList{};

struct BaseRequires{};
struct BaseExcludes{};


/**
 * Build a filter based on bitsets that shows
 * which components are active and which components are not
 * */

struct Filter {
    public:
        Filter(ComponentTypeList requires, ComponentTypeList excludes):
            m_requires(requires),
            m_excludes(excludes)
    {}

        bool passFilter(const ComponentTypeList& typeList) const;

   // private:
        ComponentTypeList m_requires;
        ComponentTypeList m_excludes;
};

/***
 * The base case for the requires or excludes template pack
 *
 * Returns a ComponentTypeList (which is an alias for std::bitset<MAX_COMPONENTS>())
 * **/
template <class... Args>
static ComponentTypeList types(TypeList<Args...> typeList) {
    
    //printf("%s\n",__PRETTY_FUNCTION__);
    return ComponentTypeList();
}


/** Builds a bitset of components recursively
 *  Using variadic templates and recursive template unpacking
 *  Eg calling this with RequireList <A,B,C,D,E> will call
 *  this function with T = A, args = <B,C,D,E,>
 *  then T = B, args = <C,D,E>
 *  etc until the basecase of args = <>
 *  in which case the empty bitset is returned
 *  */

template <class T, class... Args>
static ComponentTypeList types(TypeList<T, Args...> typeList){
    static_assert(std::is_base_of<Component,T>::value, "T must be derived from Component...");
    return ComponentTypeList().set(ComponentTypeID<T>()) | types(TypeList<Args...>());
}

/**
 * creates a filter from the component types in the require and exclude list 
 * */

template <class RequireList, class ExcludeList>
Filter MakeFilter() {
    static_assert(std::is_base_of<BaseRequires, RequireList>::value, "RequireList is not a requirement list");
    static_assert(std::is_base_of<BaseExcludes, ExcludeList>::value, "ExcludeList is not an exclude list");
    return Filter(types(RequireList{}), ComponentTypeList());//types(ExcludeList{}));
}

