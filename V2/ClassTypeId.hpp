#pragma once
#include <cstddef>


using TypeID = std::size_t;

template <typename TBase>
class ClassTypeId {
    public:
        /**
         * Create an immutable TypeID per T
         *
         * Since the counter is static only one counter per T is created
         * While any time a new type is passed as template argument a new counter
         * for that type is created.
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

