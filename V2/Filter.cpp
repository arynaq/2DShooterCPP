#include "Filter.hpp"

bool Filter::passFilter(const ComponentTypeList& typeList) const{
    /** Does it match component for component the list of require components ? */
    for(std::size_t i=0; i < m_requires.size(); ++i){
        if(!(m_requires[i] && typeList[i]))
                return false;
    }

    /** Does it match any component in the exclude list? */
    if ((m_excludes & typeList).ant())
        return false;
    return true;
}
