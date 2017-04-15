#pragma once

#include <SFML/Graphics.hpp>
#include "World.hpp"
#include "InputSystem.hpp"
#include "SpriteRenderingSystem.hpp"
#include "TextureCacheSystem.hpp"


class PacmanGame {
    public:
        PacmanGame(sf::RenderTarget& renderer);
        void init();
        bool isRunning() const {
            return m_running;
        }
        void quit(){
            m_running = false;
        }

        void update(float dt);
        void render();
        void handleEvent(sf::Event& event);

    private:
        bool m_running;
        sf::RenderTarget* m_renderTarget;
        World m_world;
        Entity m_player;

        /** Systems **/
        SpriteRenderingSystem m_spriteRenderingSystem;
        InputSystem m_inputSystem;
        TextureCacheSystem m_textureCache;

        void loadTextures();


};


