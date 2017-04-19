#include "SpriteRenderingSystem.hpp"
#include <iostream>
#include <cassert>

SpriteRenderingSystem::SpriteRenderingSystem(sf::RenderTarget& renderTarget )
    :m_renderTarget(&renderTarget)
{
}

sf::RenderTarget& SpriteRenderingSystem::getRenderTarget() const {
    assert(isValid() && "Rendertarget is null!");
    return *m_renderTarget;
}

void SpriteRenderingSystem::render(){
    auto& entities = getEntities();
    for(auto& entity : entities){
        auto& sprite = entity.getComponent<SpriteComponent>().data.sprite;
        auto& transform = entity.getComponent<TransformComponent>().transform;
        getRenderTarget().draw(sprite, transform.getTransform());
    }
}

bool SpriteRenderingSystem::isValid() const {
    return m_renderTarget != nullptr;
}
