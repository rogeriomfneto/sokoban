#pragma once

struct GameSetup {
    int screenWidth = 0;
    int screenHeight = 0;
    int tileSize = 0;
    int playerSpriteSize = 0;
    int screenTileSize = 0;
};

GameSetup& getGameSetup();

bool loadGameSetup(const char* path);
