#pragma once

#include <type_traits>
#include "Component.hpp"
#include "ClassTypeId.hpp"
#include "ComponentTypeList.hpp"

template<class... Args>
struct TypeList{};

struct BaseRequires{};
struct BaseExcludes{};

struct Filter {
    public:
        Filter(ComponentTypeList requires, ComponentTypeList excludes):
            m_requires(requires), m_excludes(excludes){
            }

        bool doesPassFilter(const ComponentTypeList& typeList) const;


    private:
        ComponentTypeList m_requires;
        ComponentTypeList m_excludes;
};

template<class... Args>
static ComponentTypeList types(TypeList<Args...> typeList){
    return ComponentTypeList();
}

template<class T, class... Args>
static ComponentTypeList types(TypeList<T, Args...> typeList){
    static_assert(std::is_base_of<Component,T>::value, "T must be derived from Component..");
    return ComponentTypeList().set(ComponentTypeId<T>()) | types(TypeList<Args...>());
}

template<class RequireList, class ExcludeList>
Filter makeFilter(){
    static_assert(std::is_base_of<BaseRequires, RequireList>::value, "RequireList must be derived from BaseRequires...");
    static_assert(std::is_base_of<BaseExcludes, ExcludeList>::value, "ExcludeList must be derived from BaseExcludes...");

    return Filter{types(RequireList{}), types(ExcludeList{})};
}

