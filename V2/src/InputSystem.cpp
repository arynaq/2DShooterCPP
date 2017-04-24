#include "InputSystem.hpp"
#include <iostream>
#include "Clock.hpp"
#include "World.hpp"
#include <cassert>

void InputSystem::update(){
    auto& entities = getEntities();
    for(auto& entity : entities){
        auto& player = entity.getComponent<PlayerComponent>();
        auto& velocity = entity.getComponent<VelocityComponent>().velocity;
        auto& direction = entity.getComponent<DirectionComponent>().direction;
        auto oldState = player.state;
        auto newState = player.state;

        if(sf::Keyboard::isKeyPressed(player.left)){
            velocity.x= -player.startSpeed;
            velocity.y = 0;
            newState = PlayerComponent::PlayerState::LEFT_MOVING;
            direction = DirectionComponent::Direction::WEST;
        }
        else if(sf::Keyboard::isKeyPressed(player.right)){
            velocity.x = player.startSpeed;
            velocity.y = 0;
            newState = PlayerComponent::PlayerState::RIGHT_MOVING;
            direction = DirectionComponent::Direction::EAST;
        }
        else if(sf::Keyboard::isKeyPressed(player.up)){
            velocity.y = -player.startSpeed;
            velocity.x = 0;
            newState = PlayerComponent::PlayerState::UP_MOVING;
            direction = DirectionComponent::Direction::NORTH;
        }
        else if(sf::Keyboard::isKeyPressed(player.down)){
            velocity.y = player.startSpeed;
            velocity.x = 0;
            newState = PlayerComponent::PlayerState::DOWN_MOVING;
            direction = DirectionComponent::Direction::SOUTH;
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
