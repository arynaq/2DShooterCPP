#include "PacmanGame.hpp"
#include "TileComponent.hpp"
#include "CollisionComponent.hpp"


PacmanGame::PacmanGame(sf::RenderTarget& renderer):
    m_renderTarget(&renderer),
    m_spriteRenderingSystem(m_world.addSystem<SpriteRenderingSystem>(renderer)),
    m_inputSystem(m_world.addSystem<InputSystem>()),
    m_spriteManagementSystem(m_world.addSystem<SpriteManagementSystem>()),
    m_movementSystem(m_world.addSystem<MovementSystem>()),
    m_tileRenderingSystem(m_world.addSystem<TileRenderingSystem>(renderer)),
    m_collisionSystem(m_world.addSystem<CollisionSystem>()),
    m_debugSystem(m_world.addSystem<DebugSystem>(renderer)),
    m_mapSystem(m_world.addSystem<MapSystem>()),
    m_AISystem(m_world.addSystem<AISystem>())
{
}


void PacmanGame::init(){
    m_player = m_world.createEntity();
    auto& spriteSheetComponent = m_player.addComponent<SpriteSheetComponent>();
    m_player.addComponent<TransformComponent>().transform.setPosition(256,480);
    m_player.addComponent<PlayerComponent>().startSpeed = 120;
    m_player.addComponent<DirectionComponent>();
    m_player.addComponent<VelocityComponent>();
    m_player.addComponent<CollisionComponent>();
    spriteSheetComponent.textureSourceID = "player";
    spriteSheetComponent.sprite.setTextureRect(sf::IntRect(0,0,32,32));


    auto ghostOne = m_world.createEntity();
    auto& spriteSheetComponentOne = ghostOne.addComponent<SpriteSheetComponent>();
    ghostOne.addComponent<TransformComponent>().transform.setPosition(256,672);
    ghostOne.addComponent<VelocityComponent>().baseSpeed = 60;
    ghostOne.addComponent<DirectionComponent>().direction = DirectionComponent::Direction::UNDEFINED;
    ghostOne.addComponent<CollisionComponent>();
    ghostOne.addComponent<AIComponent>().target = m_player;
    spriteSheetComponentOne.textureSourceID = "redghost";
    spriteSheetComponentOne.sprite.setTextureRect(sf::IntRect(0,0,32,32));

    auto ghostTwo = m_world.createEntity();
    auto& spriteSheetComponentTwo = ghostTwo.addComponent<SpriteSheetComponent>();
    ghostTwo.addComponent<TransformComponent>().transform.setPosition(350,672);
    ghostTwo.addComponent<VelocityComponent>().baseSpeed = 60;
    ghostTwo.addComponent<DirectionComponent>().direction = DirectionComponent::Direction::UNDEFINED;
    ghostTwo.addComponent<CollisionComponent>();
    ghostTwo.addComponent<AIComponent>().target = m_player;
    spriteSheetComponentTwo.textureSourceID = "blueghost";
    spriteSheetComponentTwo.sprite.setTextureRect(sf::IntRect(0,0,32,32));


    m_player.activate();
    ghostOne.activate();
    ghostTwo.activate();
    m_world.messageHandler().subscribe<PlayerStateChangedEvent>(m_spriteManagementSystem);
    m_world.messageHandler().subscribe<DirectionChangedEvent>(m_spriteManagementSystem);
    m_world.messageHandler().subscribe<DirectionChangedEvent>(m_movementSystem);
    m_world.messageHandler().subscribe<CollisionResolutionEvent>(m_movementSystem);
    m_running = true;
}

void PacmanGame::render(){
    m_renderTarget->clear(sf::Color(0x00,0x2b,0x36));
    m_tileRenderingSystem.render();
    m_spriteRenderingSystem.render();
    m_debugSystem.update(0);
}

void PacmanGame::update(float dt){
    m_world.refresh();
    m_inputSystem.update();
    m_collisionSystem.update(m_mapSystem, dt);
    m_movementSystem.update(dt);
    m_AISystem.update(m_mapSystem, dt);
    m_spriteManagementSystem.update();
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


