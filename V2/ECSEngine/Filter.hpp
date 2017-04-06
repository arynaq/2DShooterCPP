#pragma once

#include "ComponentTypeList.hpp"

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

    private:
        ComponentTypeList m_requires;
        ComponentTypeList m_excludes;
};

template <class... Args>
/** Return a bitset **/
static ComponentTypeList types(TypeList<Args...> typeList) {
    return ComponentTypeList();
}

/** Return a bitset that has field for component T turned on **/
template <class T, class... Args>
static ComponentTypeList types(TypeList<T, Args...> typeList){
    static_assert(std::is_base_of<Component,T>::value, "T must be derived from Component...");
    return ComponentTypeList().set(ComponentTypeID<T>()) | types(TypeList<Args...>());
}

template <class RequireList, class ExcludeList>
Filter MakeFilter() {
    static_assert(std::is_base_of<BaseRequires, RequireList>::value, "RequireList is not a requirement list");
    static_assert(std::is_base_of<BaseExcludes, ExcludeList>::value, "ExcludeList is not an exclude list");
    return Filter(types(RequireList{}), types(ExcludeList{}));
}

