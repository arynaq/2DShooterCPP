#include <iostream>
#include "SpriteManagementSystem.hpp"
#include <iostream>


void SpriteManagementSystem::update(){
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

void SpriteManagementSystem::receive(const DirectionChangedEvent& event){
    auto& entity = event.entity;
    auto& direction = event.direction;
    auto& spriteSheetComponent = entity.getComponent<SpriteSheetComponent>();
    int framenumber = spriteSheetComponent.framenumber;
    int framewidth = spriteSheetComponent.framewidth;
    int frameheight = spriteSheetComponent.frameheight;
    int frameCols = spriteSheetComponent.frameCols;
    if(direction == DirectionComponent::Direction::WEST){
        framenumber = spriteSheetComponent.framenumber = 0;
    }
    else if(direction == DirectionComponent::Direction::EAST){
        framenumber = spriteSheetComponent.framenumber = 1;
    }
    else if(direction == DirectionComponent::Direction::SOUTH){
        framenumber = spriteSheetComponent.framenumber = 2;
    }
    else if(direction == DirectionComponent::Direction::NORTH){
        framenumber = spriteSheetComponent.framenumber = 3;
    }
    int framex = (framenumber % frameCols) * framewidth;
    int framey = (framenumber / frameCols) * frameheight;
    sf::IntRect frameBox(framex,framey,framewidth,frameheight);
    spriteSheetComponent.sprite.setTextureRect(frameBox);
}

void SpriteManagementSystem::receive(const PlayerStateChangedEvent& event){
    auto newState = event.newState;
    auto& spriteSheetComponent = event.player.getComponent<SpriteSheetComponent>();
    int framenumber = spriteSheetComponent.framenumber;
    int framewidth = spriteSheetComponent.framewidth;
    int frameheight = spriteSheetComponent.frameheight;
    int frameCols = spriteSheetComponent.frameCols;

    if(newState == PlayerComponent::PlayerState::UP_MOVING){
        framenumber = spriteSheetComponent.framenumber = 3;
    }
    else if(newState == PlayerComponent::PlayerState::DOWN_MOVING){
        framenumber = spriteSheetComponent.framenumber = 2;
    }
    else if(newState == PlayerComponent::PlayerState::RIGHT_MOVING){
        framenumber = spriteSheetComponent.framenumber = 1;
    }
    else if(newState == PlayerComponent::PlayerState::LEFT_MOVING){
        framenumber = spriteSheetComponent.framenumber = 0;
    }
    else if(newState == PlayerComponent::PlayerState::IDLE){
    }

    int framex = (framenumber % frameCols) * framewidth;
    int framey = (framenumber / frameCols) * frameheight;
    sf::IntRect frameBox(framex,framey,framewidth,frameheight);
    spriteSheetComponent.sprite.setTextureRect(frameBox);
}
