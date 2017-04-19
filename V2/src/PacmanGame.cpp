#include "PacmanGame.hpp"


PacmanGame::PacmanGame(sf::RenderTarget& renderer):
    m_renderTarget(&renderer),
    m_spriteRenderingSystem(m_world.addSystem<SpriteRenderingSystem>(renderer)),
    m_inputSystem(m_world.addSystem<InputSystem>()),
    m_textureCache(m_world.addSystem<TextureCacheSystem>()),
    m_movementSystem(m_world.addSystem<MovementSystem>())
{
}


void PacmanGame::init(){
    m_player = m_world.createEntity();
    m_player.addComponent<SpriteComponent>().data.id = "player";
    m_player.addComponent<TransformComponent>().transform.setPosition(0,0);
    m_player.addComponent<PlayerComponent>().startSpeed = 70;
    m_player.addComponent<VelocityComponent>();
    m_player.activate();

   // m_world.messageHandler().subscribe<std::string>(m_inputSystem);
   // m_world.messageHandler().subscribe<std::string>(m_spriteRenderingSystem);
    loadTextures();
}

void PacmanGame::render(){
    m_renderTarget->clear(sf::Color(0,117,51));
    m_spriteRenderingSystem.render();
}

void PacmanGame::update(float dt){
    m_world.refresh();
    m_inputSystem.update();
    m_movementSystem.update(dt);
    m_textureCache.update();
}

void PacmanGame::handleEvent(sf::Event& event){
    switch(event.type){
        case sf::Event::Closed:
            quit();
            break;
        case sf::Event::KeyPressed:
            switch(event.key.code){
                case sf::Keyboard::Escape:
                    quit();
                    break;
                default:
                    break;
            }
        default:
            break;
    }
}


void PacmanGame::loadTextures(){
}


