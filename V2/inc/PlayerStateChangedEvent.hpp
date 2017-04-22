#pragma once
#include "PlayerComponent.hpp"

struct PlayerStateChangedEvent {
    PlayerComponent::PlayerState oldState;
    PlayerComponent::PlayerState newState;

    PlayerStateChangedEvent(PlayerComponent::PlayerState oldState, PlayerComponent::PlayerState newState):
        oldState(oldState),newState(newState){
    }
};
