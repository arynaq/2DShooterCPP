#pragma once
#include "System.hpp"
#include "SpriteComponent.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include <memory>
#include <string>

struct TextureCacheSystem : System<Requires<SpriteComponent>> {
    public:
        void update();
        using TextureMap = std::unordered_map<std::string, std::unique_ptr<sf::Texture>>;
    private:
        TextureMap m_textures;

};
