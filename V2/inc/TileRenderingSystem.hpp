#pragma once
#include "System.hpp"
#include "TileComponent.hpp"
#include "TransformComponent.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

struct TileRenderingSystem : System<Requires<TileComponent, TransformComponent>>{
    TileRenderingSystem(sf::RenderTarget& renderTarget);
    ~TileRenderingSystem(){}

    bool isValid() const;
    sf::RenderTarget& getRenderTarget() const;
    void render();

private:
    sf::RenderTarget* m_renderTarget;
};
