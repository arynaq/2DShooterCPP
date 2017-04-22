#pragma once
#include "System.hpp"
#include "Components.hpp"
#include "Events.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include "MessageHandler.hpp"

struct TileRenderingSystem:
    System<Requires<TileComponent>>,
    Receiver<TileRenderingSystem>
{
    TileRenderingSystem(sf::RenderTarget& renderTarget);
    ~TileRenderingSystem(){}

    bool isValid() const;
    void render();
    void receive(const TileCollisionEvent& event);
    sf::RenderTarget& getRenderTarget() const;

private:
    sf::RenderTarget* m_renderTarget;
};
