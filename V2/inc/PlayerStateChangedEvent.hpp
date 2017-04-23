#pragma once
#include "PlayerComponent.hpp"

struct PlayerStateChangedEvent {
    Entity player;
    PlayerComponent::PlayerState oldState;
    PlayerComponent::PlayerState newState;

    PlayerStateChangedEvent(Entity player, PlayerComponent::PlayerState oldState, PlayerComponent::PlayerState newState):
        player(player),oldState(oldState),newState(newState){
    }
};
