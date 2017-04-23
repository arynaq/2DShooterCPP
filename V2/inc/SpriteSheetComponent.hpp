#pragma once
#include "Component.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <string>

struct SpriteSheetComponent : Component {
    std::string textureSourceID;
    sf::Sprite sprite;
    
    int framenumber = 0;
    int frameRows = 1;
    int frameCols = 4;
    int framewidth = 32;
    int frameheight = 32;
};
