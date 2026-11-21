#pragma once

#include "game_state.hpp"
#include "map.hpp"
#include "player.hpp"

class PlayMode;

struct PlayResult {
    PlayMode* nextMode;
    GameState* nextState;
};

class PlayMode {
    public:
        virtual ~PlayMode() = default;
        virtual void enter(Map& map, Player& player) = 0;
        virtual PlayResult update(Map& map, Player& player) = 0;
        virtual void draw(Map& map, Player& player) = 0;
};
