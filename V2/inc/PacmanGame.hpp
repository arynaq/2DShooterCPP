#pragma once

#include <SFML/Graphics.hpp>
#include "World.hpp"
#include "InputSystem.hpp"
#include "SpriteRenderingSystem.hpp"



class PacmanGame {
    public:
        PacmanGame(sf::RenderTarget& renderer);
        void init();
        void update(float dt);
        void render();
        void handleEvent(sf::Event event);
        bool isRunning() const {
            return m_running;
        }
        void quit(){
            m_running = false;
        }

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


