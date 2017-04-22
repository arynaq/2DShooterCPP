#include "PacmanGame.hpp"
#include "TileComponent.hpp"
#include "CollisionComponent.hpp"


PacmanGame::PacmanGame(sf::RenderTarget& renderer):
    m_renderTarget(&renderer),
    m_spriteRenderingSystem(m_world.addSystem<SpriteRenderingSystem>(renderer)),
    m_inputSystem(m_world.addSystem<InputSystem>()),
    m_textureCache(m_world.addSystem<TextureCacheSystem>()),
    m_movementSystem(m_world.addSystem<MovementSystem>()),
    m_tileRenderingSystem(m_world.addSystem<TileRenderingSystem>(renderer)),
    m_collisionSystem(m_world.addSystem<CollisionSystem>()),
    m_debugSystem(m_world.addSystem<DebugSystem>(renderer)),
    m_mapSystem(m_world.addSystem<MapSystem>()),
{
}


void PacmanGame::init(){
    m_player = m_world.createEntity();
    auto& spriteSheetComponent = m_player.addComponent<SpriteSheetComponent>();
    m_player.addComponent<TransformComponent>().transform.setPosition(32,32);
    m_player.addComponent<PlayerComponent>().startSpeed = 100;
    m_player.addComponent<VelocityComponent>();
    m_player.addComponent<CollisionComponent>().collisionBox;
    spriteSheetComponent.textureSourceID = "player";
    spriteSheetComponent.sprite.setTextureRect(sf::IntRect(0,0,32,32));

    auto ghostOne = m_world.createEntity();
    auto& velocityComponentOne = ghostOne.addComponent<VelocityComponent>().velocity;
    auto& spriteSheetComponentOne = ghostOne.addComponent<SpriteSheetComponent>();
    ghostOne.addComponent<CollisionComponent>().collisionBox;
    spriteSheetComponentOne.textureSourceID = "orangeghost";
    spriteSheetComponentOne.sprite.setTextureRect(sf::IntRect(32,0,32,32));
    ghostOne.addComponent<TransformComponent>().transform.setPosition(172,172);
    velocityComponentOne.x = 200;
    m_player.activate();
    ghostOne.activate();



   // m_world.messageHandler().subscribe<std::string>(m_inputSystem);
   // m_world.messageHandler().subscribe<std::string>(m_spriteRenderingSystem);
    m_world.messageHandler().subscribe<TileCollisionEvent>(m_collisionSystem);
    m_world.messageHandler().subscribe<TileCollisionEvent>(m_tileRenderingSystem);
    loadTextures();
    m_running = true;
}

void PacmanGame::render(){
    m_renderTarget->clear(sf::Color(0xFF,0xFF,0xFF));
    m_tileRenderingSystem.render();
    m_spriteRenderingSystem.render();
    m_debugSystem.update(0);
}

void PacmanGame::update(float dt){
    m_world.refresh();
    m_inputSystem.update();
    m_movementSystem.update(dt);
    m_textureCache.update();
    m_collisionSystem.update(m_mapSystem,dt);
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


