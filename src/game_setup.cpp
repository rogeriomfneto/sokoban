#include "game_setup.h"
#include "json.hpp"
#include <fstream>
#include <iostream>

static GameSetup loadedSetup;

GameSetup& getGameSetup() {
    return loadedSetup;
}

bool loadGameSetup(const char* path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open game setup: " << path << "\n";
        return false;
    }

    try {
        nlohmann::json json;
        file >> json;

        GameSetup& setup = getGameSetup();
        setup.screenWidth = json.at("screenWidth").get<int>();
        setup.screenHeight = json.at("screenHeight").get<int>();
        setup.tileSize = json.at("tileSize").get<int>();
        setup.playerSpriteSize = json.at("playerSpriteSize").get<int>();
        setup.screenTileSize = json.at("screenTileSize").get<int>();
    } catch (const nlohmann::json::exception& error) {
        std::cerr << "Failed to parse game setup: " << error.what() << "\n";
        return false;
    }

    return true;
}
