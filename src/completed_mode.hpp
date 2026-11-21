#pragma once

#include "map.hpp"
#include "player.hpp"
#include "play_mode.hpp"

class CompletedMode : public PlayMode {
    public:
        CompletedMode();

        void enter(Map& map, Player& player) override;
        PlayResult update(Map& map, Player& player) override;
        void draw(Map& map, Player& player) override;
};
