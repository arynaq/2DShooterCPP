#include "SpriteRenderingSystem.hpp"


SpriteRenderingSystem::SpriteRenderingSystem(sf::RenderTarget& renderTarget )
    :m_renderTarget(&renderTarget)
{
}

void SpriteRenderingSystem::render(){
    getEntities();
}
