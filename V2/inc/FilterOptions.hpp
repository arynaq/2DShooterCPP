#pragma once
#include "Filter.hpp"

template <class... Args>
struct Requires : TypeList<Args...>, BaseRequires {};
template <class... Args>
struct Excludes : TypeList<Args...>, BaseExcludes {};
