#pragma once
#include "Component.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <vector>

using SpriteFrames = std::vector<sf::IntRect>;
struct SpriteSheetComponent : Component {
    sf::Sprite sprite;
    SpriteFrames frames;
    int framenumber;
    int framewidth = 32;
    int frameheight = 32;
    std::string textureSourceID;
};
