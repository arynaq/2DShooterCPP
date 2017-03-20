#pragma once

#include "Component.hpp"
#include <SFML/Graphics/Sprite.hpp>

struct SpriteComponent : Component {
    sf::Sprite sprite;
};
