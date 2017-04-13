#include <iostream>
#include "Entity.hpp"
#include "System.hpp"
#include "World.hpp"
#include "InputSystem.hpp"
#include <string>

#include <boost/signals2/signal.hpp>

struct B {
    void operator()() const {
        std::cout<<"Hello from B!"<<std::endl;
    }

    void operator()(const std::string& s) const {
        std::cout<<"B was passed: " << s<<std::endl;
    }
};


template <typename TDerived, typename ValueType>
struct Base {
    boost::signals2::signal<void(const ValueType&)> signal;
};


template <typename T>
struct Derived : Base<Derived<T>, T>{
    using value_type = T;
    value_type value;
    Derived(value_type&& rvalue) : value(std::move(rvalue)){}
};



int main(){
    InputSystem s;
    B b1;

    Derived<std::string> d(std::string("Hello"));
    d.signal.connect(b1);
    d.signal("Foo!");
    return 0;
}


/** Ideas:
 *  Create a publisher / subscriber system for the game
 *
 *  a) Can use filtering to match a system (subscriber) to a message (Filter & std::forward with vargs)
 *  b) Can let a system also be a publisher
 *  c) On a message generation -> Pass to mediator (world)
 *  d) World is responsible in refresh for sending messges to correct system
 *  e) What is a message then? A struct with a datafield where entity is referenced and a copy of the 
 *  f) data to be changed is.
 *  
 *  Eg: auto& someEntity = ....
 *      auto& Message = getWorld().createEntity();
 *      Message.addComponent<VelocityComponent>().velocity = {2,2};
 *      Message.addComponent<EntityMessageComponent>().entity = someEntity;
 *      Message.activate();
 *      getWorld().MessageHandler.refresh() --> sends messages to correct systems
 *      then in world.refresh()
 *      messageHandler.refresh() -> Which simply adds a message to the correct system
 *      
 *           -- implicit that requires EntityMessageComponent -- 
 *      struct VelocityMessageHandler : MessageHandler<Requires<VelocityComponent>>
 *      or struct VelocityMessageHandler : MessageHandler<VelocityComponent>
 *
 *
 *      and in that handlers update:
 *              void update(){
 *                  getEntities();
 *              }
 *
 *
 *   
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *  **/
