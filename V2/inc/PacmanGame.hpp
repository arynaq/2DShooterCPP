#pragma once

#include <SFML/Graphics.hpp>
#include "World.hpp"
#include "InputSystem.hpp"
#include "SpriteRenderingSystem.hpp"
#include "TextureCacheSystem.hpp"
#include "MovementSystem.hpp"
#include "MessageHandler.hpp"


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
    
        const double frame_dt = 1.0/30;

    private:
        bool m_running;
        sf::RenderTarget* m_renderTarget;
        World m_world;
        Entity m_player;
        MessageHandler m_messageHandler;

        /** Systems **/
        SpriteRenderingSystem& m_spriteRenderingSystem;
        InputSystem& m_inputSystem;
        TextureCacheSystem& m_textureCache;
        MovementSystem& m_movementSystem;
        void loadTextures();


};


