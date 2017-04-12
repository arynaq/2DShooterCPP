#pragma once

#include "Component.hpp"
#include <SFML/Window/Keyboard.hpp>

struct PlayerComponent : Component {
    using Key = sf::Keyboard::Key;
    float startSpeed;
    enum class PlayerState {
        IDLE = 0,
        LEFT_MOVING,
        RIGHT_MOVING,
        DOWN_MOVING,
        UP_MOVING
    } state;
    const Key left = Key::A;
    const Key right = Key::D;
    const Key up = Key::W;
    const Key down = Key::S;
};
