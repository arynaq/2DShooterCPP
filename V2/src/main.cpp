#include <iostream>
#include "Entity.hpp"
#include "System.hpp"
#include "World.hpp"
#include "InputSystem.hpp"
#include <string>
#include <boost/signals2/signal.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/function.hpp>



struct ComponentChanged{
    ComponentChanged(Component c, Entity e) : changedComponent(c), entity(e) {}
    Component changedComponent;
    Entity entity;
    int value = 332124;
};


struct BaseEvent {
    protected:
        static TypeID m_nextTypeID;
};

TypeID BaseEvent::m_nextTypeID = 0;

template <typename TSubEvent>
struct Event : BaseEvent {
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
struct Receiver{
private:
    friend class EventManager;
    boost::ptr_map<TypeID, boost::signals2::connection> connections;
};



struct EventManager {
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

    private:
        SignalMap map;
};

struct IntEvent {
    int value = 11;
};

struct Test : Receiver<Test>{
    void receive(const IntEvent& e){
        std::cout<<"Received event with value: " <<e.value<<std::endl;
    }
    void receive(const std::string& s){
        std::cout<<"Received event with string value: " << s << std::endl;
    }
};






int main(){
    InputSystem s;
    EventManager m;
    Test test;
    m.subscribe<IntEvent>(test);
    m.subscribe<std::string>(test);

    const IntEvent i;
    const std::string h("Hello World!");
    m.emit(i);
    m.emit(h);

    m.unsubscribe<std::string>(test);
    m.emit(h);
    m.emit(i);

    return 0;
}


