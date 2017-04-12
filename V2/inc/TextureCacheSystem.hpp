#pragma once
#include "System.hpp"
#include "SpriteComponent.hpp"
#include <vector>
#include <algorithm>

struct TextureCacheSystem : System<Requires<SpriteComponent>> {
    public:
        void update();
};
