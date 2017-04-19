#pragma once
#include "System.hpp"
#include "PlayerComponent.hpp"
#include "VelocityComponent.hpp"
#include "MessageHandler.hpp"
#include <string>

struct InputSystem : System<Requires<PlayerComponent, VelocityComponent>>, Receiver<InputSystem>{
    public:
        void receive(const std::string& s){
            std::cout<<"Inputsystem received string: " << s << std::endl;
        }
        void update();
        ~InputSystem(){}
};
