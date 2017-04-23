#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include <memory>
#include <string>

#include "System.hpp"
#include "Components.hpp"
#include "Events.hpp"
#include "MessageHandler.hpp"

struct SpriteManagementSystem:
    System<Requires<SpriteSheetComponent>>,
    Receiver<SpriteManagementSystem>
{
    public:
        void update();
        void receive(const PlayerStateChangedEvent& event);
    private:
        using TextureMap = std::unordered_map<std::string, std::unique_ptr<sf::Texture>>;
        TextureMap m_textures;
};
