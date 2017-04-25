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
        auto& shape = entity.getComponent<TileComponent>().shape;
        if(entity.getComponent<TileComponent>().tagged){
            shape.setFillColor(sf::Color::Cyan);
        }
        else {
            shape.setFillColor(sf::Color::Transparent);
        }
        getRenderTarget().draw(shape);
    }
}

void TileRenderingSystem::receive(const TileCollisionEvent& event){
    event.tile.getComponent<TileComponent>().shape.setFillColor(sf::Color::Blue);
}
