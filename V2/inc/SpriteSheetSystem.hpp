#pragma once

#include "System.hpp"
#include "Components.hpp"
#include "Events.hpp"
#include "MessageHandler.hpp"

struct SpriteSheetSystem:
    System<Requires<SpriteSheetComponent>>,
    Receiver<SpriteSheetSystem>
{
    void receive(const PlayerStateChangedEvent& event);
};
