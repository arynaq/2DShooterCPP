#pragma once

struct TileCollisionEvent{
    Entity entity;
    Entity tile;

    TileCollisionEvent(Entity entity, Entity tile) :
        entity(entity), tile(tile){}
};
