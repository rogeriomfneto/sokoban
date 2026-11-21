#pragma once

#include <string>
#include "game_state.hpp"
#include "map.hpp"
#include "player.hpp"
#include "play_mode.hpp"

class PlayState : public GameState {
    private:
        PlayMode* playMode = nullptr;
    public:
        PlayState(const char* levelName);
        ~PlayState() override;

        void enter() override;
        GameState* update() override;
        void draw() override;

        std::string levelName;
        Map map;
        Player player;
};
