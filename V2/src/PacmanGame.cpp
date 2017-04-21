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
    m_debugSystem(m_world.addSystem<DebugSystem>(renderer))
{
}


void PacmanGame::init(){
    m_player = m_world.createEntity();
    m_player.addComponent<SpriteComponent>().data.id = "player";
    m_player.addComponent<TransformComponent>().transform.setPosition(32,32);
    m_player.addComponent<PlayerComponent>().startSpeed = 100;
    m_player.addComponent<VelocityComponent>();
    m_player.addComponent<CollisionComponent>();
    m_player.activate();


    const int map[32][32] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    for(int i=0; i<32; ++i){
        for(int j=0; j<32; ++j){
            std::cout<<map[i][j]<<std::endl;
            auto tile = m_world.createEntity();
            auto& tileComponent = tile.addComponent<TileComponent>();
            tile.addComponent<TransformComponent>().transform.setPosition(j*32, i*32);
            if(map[i][j] == 1){
                tileComponent.shape.setFillColor(sf::Color::Red);
                auto& collisionComponent = tile.addComponent<CollisionComponent>();
                collisionComponent.collisionBox.left = (j*32) + 1;
                collisionComponent.collisionBox.top  = (i*32) + 1;
                collisionComponent.collisionBox.width = 31;
                collisionComponent.collisionBox.height = 31;
            }
            if(map[i][j] == 0)
                tileComponent.shape.setFillColor(sf::Color::Black);
            tile.activate();
        }
    }

   // m_world.messageHandler().subscribe<std::string>(m_inputSystem);
   // m_world.messageHandler().subscribe<std::string>(m_spriteRenderingSystem);
    m_world.messageHandler().subscribe<CollisionEvent>(m_movementSystem);
    loadTextures();
    m_running = true;
}

void PacmanGame::render(){
    m_renderTarget->clear(sf::Color(0,117,51));
    m_tileRenderingSystem.render();
    m_spriteRenderingSystem.render();

    m_debugSystem.update(0);
}

void PacmanGame::update(float dt){
    m_world.refresh();
    m_inputSystem.update();
    m_movementSystem.update(dt);
    m_textureCache.update();
    m_collisionSystem.update(dt);
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


