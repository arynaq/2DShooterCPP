#pragma once

#include "Component.hpp"
#include <SFML/Window/Keyboard.hpp>

struct PlayerComponent : Component {

    float startSpeed;

    enum class PlayerState {
        DEFAULT = 0,
        LEFT_MOVING,
        RIGHT_MOVING,
        DOWN_MOVING,
        UP_MOVING,
        IDLE
    } state;

    struct Controls {
        using Key = sf::Keyboard::Key;
        Controls() : left(Key::A), right(Key::D), up(Key::W), down(Key::S){
        }
        Key left, right, up, down;
    } controls;
};
