#pragma once
#include "Component.hpp"
#include <SFML/Graphics/Sprite.hpp>


struct SpriteComponent : Component {
    struct Texture {
        sf::Sprite* sprite;
        sf::String id;
    } texture;
};
