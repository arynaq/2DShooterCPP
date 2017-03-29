#pragma once
#include <cstddef>


using TypeID = std::size_t;

template <typename TBase>
class ClassTypeId {
    public:
        /**
         * Create an immutable TypeID per T
         * */
        template <typename T>
        static TypeID GetTypeID(){
            static const TypeID id = m_nextTypeID++;
            return id;
        }
    private:
        static TypeID m_nextTypeID;

};

template <typename TBase>
TypeID ClassTypeId<TBase>::m_nextTypeID = 0;

