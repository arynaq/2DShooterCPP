#include "PacmanGame.hpp"


PacmanGame::PacmanGame(sf::RenderTarget& renderer):
    m_renderTarget(&renderer),
    m_spriteRenderingSystem(renderer)
{
}


void PacmanGame::init(){
    m_world.addSystem(m_spriteRenderingSystem);
    m_world.addSystem(m_inputSystem);
    m_player = m_world.createEntity();

    auto& playerSprite = m_player.addComponent<SpriteComponent>().sprite;
}

void PacmanGame::render(){
    m_spriteRenderingSystem.render();
}

void PacmanGame::update(float dt){
}

void PacmanGame::handleEvent(sf::Event event){
}


void PacmanGame::loadTextures(){
}


