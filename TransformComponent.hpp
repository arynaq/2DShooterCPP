#pragma once

#include "Component.hpp"
#include <SFML/Graphics/Tranformable.hpp>

struct TransformComponent : Component {
    sf::Transformable transform;
};
