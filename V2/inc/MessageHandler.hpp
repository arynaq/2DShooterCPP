#pragma once

#include <boost/signals2/signal.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/function.hpp>
#include "ClassTypeId.hpp"


/**
 * @TODO: 
 * - As it is now any subscriber to event of type T has to implement
 *   void receive(const T&)
 *   which is cumbersome and not maintainable if we have to subscribe to a billion different Ts of events
 *   There is also the problem of T having to be a known type.
 *
 *   - Feature-> Store functors/delegates of matching varargs so that I can send all the data in one function instead of wrapping it in T
 * */


class BaseEvent {
    protected:
        static TypeID m_nextTypeID;
};


template <typename TSubEvent>
class Event : BaseEvent {
public:
    static TypeID  getID(){
        static const TypeID id = m_nextTypeID++;
        return id;
    }
};


/**
 * CRTP to make sure only one connection map exist per subclass
 *
 * Keep a list of the connections that are made, check against this when trying to disconnect a signal/slot
 * **/
template <typename Derived>
class Receiver{
private:
    friend class MessageHandler;
    boost::ptr_map<TypeID, boost::signals2::connection> connections;
};



class MessageHandler{
public: 
    using Signal = boost::signals2::signal<void(const void*)>;
    using SignalMap = boost::ptr_map<TypeID, Signal>;


    /** Add the receive function of the subscriber 
     * as a slot to the signal map of the given Event type
     *
     * So that whenever emit<E> is called all previously slots
     * connected to E here will be called.
     * */
    template <typename E, typename Subscriber>
    void subscribe(Subscriber& subscriber){
        /** Cannot use auto for the callback, as overloaded functions will fudge up... **/
        static_assert(std::is_base_of<Receiver<Subscriber>, Subscriber>::value, "Subscriber must derive from receiver!..");
        void (Subscriber::*callback)(const E&) = &Subscriber::receive;
        auto callbackWrapper = CallbackWrapper<E>(boost::bind(callback, &subscriber, _1));
        TypeID id = Event<E>::getID();  
        auto connection = map[id].connect(callbackWrapper);
        subscriber.connections[id]= connection;
    }

    template <typename E, typename Subscriber>
    void unsubscribe(Subscriber& subscriber){
        TypeID id = Event<E>::getID();
        auto& connection = subscriber.connections[id];
        connection.disconnect();
    }


    template <typename E>
    void emit(const E& event){
        auto id = Event<E>::getID();
        map[id](&event);
    }



private:
    SignalMap map;
    /** Since we can only store functions of void return type and const void* input 
     *  we need to wrap void (const E&) inside a functor
     *  and cast back on operator()
     *  */
    template <typename E>
    struct CallbackWrapper {
        explicit CallbackWrapper(boost::function<void(const E&)> callback) :callback(callback)
        {
        }
        void operator()(const void* event){
            callback(*(static_cast<const E*>(event)));
        }
        boost::function<void(const E&)> callback;
    };
};



