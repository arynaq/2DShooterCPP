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

template <class...Args>
static ComponentTypeList types(TypeList<Args...> typelist) {
    return ComponentTypeList();
}

template <class T, class...Args>
static ComponentTypeList types(

