#include "game_setup.h"
#include "json.hpp"
#include <iostream>
#include <raylib.h>

static GameSetup loadedSetup;

GameSetup& getGameSetup() {
    return loadedSetup;
}

bool loadGameSetup(const char* path) {
    char* text = LoadFileText(path);
    if (text == nullptr) {
        std::cerr << "Failed to open game setup: " << path << "\n";
        return false;
    }

    try {
        nlohmann::json json = nlohmann::json::parse(text);

        GameSetup& setup = getGameSetup();
        setup.screenWidth = json.at("screenWidth").get<int>();
        setup.screenHeight = json.at("screenHeight").get<int>();
        setup.tileSize = json.at("tileSize").get<int>();
        setup.playerSpriteSize = json.at("playerSpriteSize").get<int>();
        setup.screenTileSize = json.at("screenTileSize").get<int>();
        setup.tilesetPath = json.at("tilesetPath").get<std::string>();
        setup.playerSpritePath = json.at("playerSpritePath").get<std::string>();
    } catch (const nlohmann::json::exception& error) {
        std::cerr << "Failed to parse game setup: " << error.what() << "\n";
        UnloadFileText(text);
        return false;
    }

    UnloadFileText(text);
    return true;
}
