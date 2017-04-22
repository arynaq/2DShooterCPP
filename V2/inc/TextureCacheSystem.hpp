#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include <memory>
#include <string>

#include "System.hpp"
#include "Components.hpp"

struct TextureCacheSystem : System<Requires<SpriteSheetComponent>> {
    public:
        void update();
        using TextureMap = std::unordered_map<std::string, std::unique_ptr<sf::Texture>>;
    private:
        TextureMap m_textures;

};
