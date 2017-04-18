#include "PacmanGame.hpp"


PacmanGame::PacmanGame(sf::RenderTarget& renderer):
    m_spriteRenderingSystem(m_world.addSystem<SpriteRenderingSystem>(renderer)),
    m_inputSystem(m_world.addSystem<InputSystem>()),
    m_textureCache(m_world.addSystem<TextureCacheSystem>())
{
}


void PacmanGame::init(){
    m_player = m_world.createEntity();
    m_player.addComponent<SpriteComponent>().texture.id = "player";
}

void PacmanGame::render(){
    m_spriteRenderingSystem.render();
}

void PacmanGame::update(float dt){
    m_world.refresh();
    m_inputSystem.update();
    m_textureCache.update();
}

void PacmanGame::handleEvent(sf::Event& event){
}


void PacmanGame::loadTextures(){
}


