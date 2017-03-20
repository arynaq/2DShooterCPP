#include "Filter.hpp"

bool Filter::doesPassFilter(const ComponentTypeList& typeList) const {
    for(std::size_t i=0; i<m_requires.size(); ++i){
        if(m_requires[i] == true && typeList[i] == false){
            return false;
        }

        if((m_excludes & typeList).any()){
            return false;
        }
    }
    return true;
}
