#pragma once

#include "map.hpp"
#include "player.hpp"
#include "play_mode.hpp"

class RunningMode : public PlayMode {
    private:
        bool allBoxesInPlace(Map& map);
    public:
        RunningMode();

        void enter(Map& map, Player& player) override;
        PlayResult update(Map& map, Player& player) override;
        void draw(Map& map, Player& player) override;

        int xOffset = 0;
        int yOffset = 0;
};
