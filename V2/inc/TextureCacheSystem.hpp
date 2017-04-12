#pragma once
#include "System.hpp"
#include "SpriteComponent.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <string>

struct TextureCacheSystem : System<Requires<SpriteComponent>> {
    public:
        void update();
        using TextureMap = std::map<std::string, sf::Texture>;
    private:
        TextureMap m_textures;

};
