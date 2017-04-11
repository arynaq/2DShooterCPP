#pragma once
#include "System.hpp"
#include "PlayerComponent.hpp"
#include "VelocityComponent.hpp"

struct InputSystem : System<Requires<PlayerComponent, VelocityComponent>> {
    public:
        void update(float dt);
    private:
        void setPlayerState(Entity& entity, PlayerComponent& p, PlayerComponent::PlayerState state);
};
