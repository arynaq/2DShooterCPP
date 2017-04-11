#pragma once

#include <SFML/Graphics.hpp>
#include "World.hpp"
#include "InputSystem.hpp"
#include "SpriteRenderingSystem.hpp"


using EntityArray = World::EntityArray;

class PacmanGame {
    public:
        PacmanGame(sf::RenderTarget& renderer) : m_renderer(&renderer){}
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
        sf::RenderTarget* m_renderer;
        World m_world;
        Entity m_player;
        EntityArray m_entities;

        /** Systems **/
        SpriteRenderingSystem m_spriteRenderer;
        InputSystem m_inputsystem;
};


