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
        auto& oldVelocity = entity.getComponent<VelocityComponent>().prevVelocity;
        auto oldState = player.state;
        auto newState = player.state;

        if(sf::Keyboard::isKeyPressed(player.left)){
            velocity.x= -player.startSpeed;
            velocity.y = 0;
            newState = PlayerComponent::PlayerState::LEFT_MOVING;
            oldVelocity = velocity;
        }
        else if(sf::Keyboard::isKeyPressed(player.right)){
            velocity.x = player.startSpeed;
            velocity.y = 0;
            newState = PlayerComponent::PlayerState::RIGHT_MOVING;
            oldVelocity = velocity;
        }
        else if(sf::Keyboard::isKeyPressed(player.up)){
            velocity.y = -player.startSpeed;
            velocity.x = 0;
            newState = PlayerComponent::PlayerState::UP_MOVING;
            oldVelocity = velocity;
        }
        else if(sf::Keyboard::isKeyPressed(player.down)){
            velocity.y = player.startSpeed;
            velocity.x = 0;
            newState = PlayerComponent::PlayerState::DOWN_MOVING;
            oldVelocity = velocity;
        }

        else {
            velocity.x = 0;
            velocity.y = 0;
        }

        if(oldState != newState){
            getWorld().messageHandler().emit<PlayerStateChangedEvent>(entity, oldState,newState);
        }
    }
}
