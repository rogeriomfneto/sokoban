#pragma once

#include <string>
#include "game_state.h"
#include "map.h"
#include "player.h"

class PlayState : public GameState {
    public:
        PlayState(const char* levelName);

        void enter() override;
        GameState* update() override;
        void draw() override;

        std::string levelName;
        Map map;
        Player player;
        int xOffset = 0;
        int yOffset = 0;
};
