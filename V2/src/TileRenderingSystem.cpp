#include "TileRenderingSystem.hpp"
#include <cassert>

TileRenderingSystem::TileRenderingSystem(sf::RenderTarget& renderTarget) :
    m_renderTarget(&renderTarget){
}

bool TileRenderingSystem::isValid() const {
    return m_renderTarget != nullptr;
}

sf::RenderTarget& TileRenderingSystem::getRenderTarget() const {
    assert(isValid() && "Rendertarget is null...");
    return *m_renderTarget;
}

void TileRenderingSystem::render(){
    auto& entities = getEntities();
    for(auto& entity : entities){
        auto& tileComponent = entity.getComponent<TileComponent>();
        auto& shape = tileComponent.shape;
        getRenderTarget().draw(shape);
    }
}
