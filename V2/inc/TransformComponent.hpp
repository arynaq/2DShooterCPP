#pragma once

#include "Component.hpp"
#include <SFML/Graphics/Transformable.hpp>

struct TransformComponent : Component {
    sf::Transformable transform;
};
