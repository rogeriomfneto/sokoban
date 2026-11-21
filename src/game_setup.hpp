#pragma once

#include <string>
#include <raylib.h>

struct GameSetup {
    int screenWidth = 0;
    int screenHeight = 0;
    int tileSize = 0;
    int playerSpriteSize = 0;
    int screenTileSize = 0;
    std::string tilesetPath;
    std::string playerSpritePath;
    std::string levelsPath;
    int menuSelectedFontSize = 0;
    int menuUnselectedFontSize = 0;
    int menuLineHeight = 0;
    Color menuSelectedColor = WHITE;
    Color menuUnselectedColor = GRAY;
    std::string completedHeaderText;
    std::string completedCaptionText;
};

GameSetup& getGameSetup();

bool loadGameSetup(const char* path);
