#pragma once
#include "System.hpp"
#include "SpriteComponent.hpp"
#include "TransformComponent.hpp"
#include <SFML/Graphics/RenderTarget.hpp>




struct SpriteRenderingSystem : System<Requires<SpriteComponent, TransformComponent>> {
    public:
        SpriteRenderingSystem(sf::RenderTarget& renderTarget);
        void render();
        sf::RenderTarget& getRenderTarget() const;

    private:
        sf::RenderTarget* m_renderTarget;

};
