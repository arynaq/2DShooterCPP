#include "DebugSystem.hpp"
#include <iostream>


DebugSystem::DebugSystem(sf::RenderTarget& renderTarget) :
    renderTarget(&renderTarget)
{
}

void DebugSystem::update(double dt){
    auto& entities = getEntities();
    sf::RectangleShape shape;
    for(auto& entity : entities){
        auto& rect = entity.getComponent<CollisionComponent>().collisionBox;
        shape.setSize(sf::Vector2f(rect.width,rect.height));
        shape.setPosition(sf::Vector2f(rect.left, rect.top));
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineThickness(1);
        shape.setOutlineColor(sf::Color::Blue);
        std::cout<<","<<shape.getSize().x<<","<<shape.getSize().y<<std::endl;
        renderTarget->draw(shape);
    }
}
