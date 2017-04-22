#pragma once

#include "System.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include "MessageHandler.hpp"
#include "Components.hpp"




struct SpriteRenderingSystem : System<Requires<SpriteSheetComponent, TransformComponent>>, Receiver<SpriteRenderingSystem> {
    public:
        SpriteRenderingSystem(sf::RenderTarget& renderTarget);
        /**
        void receive(const std::string& msg){
            std::cout<<"Spriterenderere received: " << msg << std::endl;
        }
        **/
        ~SpriteRenderingSystem(){}
        void render();
        sf::RenderTarget& getRenderTarget() const;
        bool isValid() const;

    private:
        sf::RenderTarget* m_renderTarget;
};
