#include "TextureCacheSystem.hpp"
#include <iostream>


void TextureCacheSystem::update(){
    auto& entities = getEntities();
    for(auto& entity : entities){
        auto& spriteSheetComponent = entity.getComponent<SpriteSheetComponent>();
        auto& id = spriteSheetComponent.textureSourceID;
        auto find = m_textures.find(id);
        /** Texture not found **/
        if(find == m_textures.end()){
            m_textures[id].reset(new sf::Texture());
            auto& texture = *m_textures[id];
            if(texture.loadFromFile("res/textures/"+id+".png")){
                spriteSheetComponent.sprite.setTexture(texture);
            }
        }
        /** Texture found **/
        else {
            // @Todo: check if textures match with id, if not a new texture has been set
            // Must notify listeners
        }
    }
}
