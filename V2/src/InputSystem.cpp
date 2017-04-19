#include "InputSystem.hpp"
#include <iostream>
#include "Clock.hpp"
#include "World.hpp"
#include <cassert>

void InputSystem::update(){
    auto& entities = getEntities();
    //auto playerEntities = getWorld().getEntities<Requires<PlayerComponent>>();
    for(auto& entity : entities){
        auto& player = entity.getComponent<PlayerComponent>();
        auto& velocity = entity.getComponent<VelocityComponent>().velocity;

        if(sf::Keyboard::isKeyPressed(player.left)){
            getWorld().messageHandler().emit<std::string>("Left key pressed..");
            velocity.x= -player.startSpeed;
            velocity.y = 0;
        }
        else if(sf::Keyboard::isKeyPressed(player.right)){
            velocity.x = player.startSpeed;
            velocity.y = 0;
        }
        else if(sf::Keyboard::isKeyPressed(player.up)){
            velocity.y = -player.startSpeed;
            velocity.x = 0;
        }
        else if(sf::Keyboard::isKeyPressed(player.down)){
            velocity.y = player.startSpeed;
            velocity.x = 0;
        }
        else {
            velocity.x = 0;
            velocity.y = 0;
        }
    }
}
