#pragma once
#include "System.hpp"
#include "SpriteComponent.hpp"
#include "TransformComponent.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include "MessageHandler.hpp"
#include <string>
#include <iostream>




struct SpriteRenderingSystem : System<Requires<SpriteComponent, TransformComponent>>, Receiver<SpriteRenderingSystem> {
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
