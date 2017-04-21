#pragma once
#include "System.hpp"
#include "Components.hpp"
#include <SFML/Graphics.hpp>

struct DebugSystem : System<Requires<CollisionComponent>>{
    sf::RenderTarget* renderTarget;
    DebugSystem(sf::RenderTarget& renderTarget);
    void update(double dt);
};
