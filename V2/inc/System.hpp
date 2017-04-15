#pragma once
#include "BaseSystem.hpp"
#include "ClassTypeId.hpp"
#include "FilterOptions.hpp"

template <class RequireList, class ExcludeList = Excludes<>>
class System : public BaseSystem {

    public:
        System() : BaseSystem(MakeFilter<RequireList, ExcludeList>())
        {
        }

};

/** As the other TypeIDs this ensures that we get a unique identifier per new
 * class deriving from BaseSystem
 * */
template <class T>
TypeID SystemTypeId(){
    return ClassTypeId<BaseSystem>::GetTypeID<T>();
}
