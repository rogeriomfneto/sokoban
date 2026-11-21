#pragma once

#include <raylib.h>
#include "direction.hpp"
#include "map.hpp"

class Player {
    public:
        Vector2 pos = {0, 0};
        Texture2D texture = {};

        void tryMove(Map& map, Direction direction);
};
