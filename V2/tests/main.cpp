#include <iostream>
#include "Entity.hpp"
#include "System.hpp"
#include "World.hpp"
#include "InputSystem.hpp"
#include <string>
#include "MessageHandler.hpp"


struct ComponentChanged{
    ComponentChanged(Component c, Entity e) : changedComponent(c), entity(e) {}
    Component changedComponent;
    Entity entity;
    int value = 332124;
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


