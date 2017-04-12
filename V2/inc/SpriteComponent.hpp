#pragma once
#include "Component.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <string>


struct SpriteComponent : Component {
    struct Texture {
        sf::Sprite* sprite;
        std::string id;
    } texture;
};
