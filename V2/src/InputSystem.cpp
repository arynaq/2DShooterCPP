#include "InputSystem.hpp"
#include <iostream>
#include "Clock.hpp"


void InputSystem::update(){
    auto entities = getEntities();
    for(auto& entity : entities){
        auto& player = entity.getComponent<PlayerComponent>();
        auto& velocity = entity.getComponent<VelocityComponent>().velocity;

        if(sf::Keyboard::isKeyPressed(player.left)){
            std::cout<<"Pressed left.."<<std::endl;
            velocity.x= -player.startSpeed;
            velocity.y = 0;
        }
        else if(sf::Keyboard::isKeyPressed(player.right)){
            std::cout<<"Pressed right.."<<std::endl;
            velocity.x = player.startSpeed;
            velocity.y = 0;
        }
        else if(sf::Keyboard::isKeyPressed(player.up)){
            std::cout<<"Pressed up.."<<std::endl;
            velocity.y = -player.startSpeed;
            velocity.x = 0;
        }
        else if(sf::Keyboard::isKeyPressed(player.down)){
            std::cout<<"Pressed down.."<<std::endl;
            velocity.y = player.startSpeed;
            velocity.x = 0;
        }
    }
}
