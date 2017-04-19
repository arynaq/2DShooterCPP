#include "TextureCacheSystem.hpp"
#include <iostream>


void TextureCacheSystem::update(){
    auto& entities = getEntities();
    for(auto& entity : entities){
        auto& spriteComponent = entity.getComponent<SpriteComponent>();
        auto& data = spriteComponent.data;
        auto find = m_textures.find(data.id);
        /** Texture not found **/
        if(find == m_textures.end()){
            m_textures[data.id].reset(new sf::Texture());
            auto& texture = *m_textures[data.id];
            if(texture.loadFromFile("res/textures/"+data.id+".png")){
                spriteComponent.data.sprite.setTexture(texture,true);
            }
        }
        /** Texture found **/
        else {
            // @Todo: check if textures match with id, if not a new texture has been set
            // Must notify listeners
        }
    }
}
