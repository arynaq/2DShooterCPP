#include "TextureCacheSystem.hpp"


void TextureCacheSystem::update(){
    auto& entities = getEntities();
    for(auto& entity : entities){
        auto& spriteComponent = entity.getComponent<SpriteComponent>();
        auto& texture = spriteComponent.texture;
        auto find = m_textures.find(texture.id);
        /** Texture not found **/
        if(find == m_textures.end()){
            if(!m_textures[texture.id].loadFromFile("res/textures/"+texture.id+".png")){
            }
        }
        /** Texture found **/
        else {
            // @Todo: check if textures match with id, if not a new texture has been set
            // Must notify listeners
        }
    }
}
