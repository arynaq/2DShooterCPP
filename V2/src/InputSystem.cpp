#include "InputSystem.hpp"


void InputSystem::update(float dt){
    auto entities = getEntities();
    for(auto& entity : entities){
        auto& player = entity.getComponent<PlayerComponent>();
        auto& velocity = entity.getComponent<VelocityComponent>().velocity;

        if(sf::Keyboard::isKeyPressed(player.left)){
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
    }
}
