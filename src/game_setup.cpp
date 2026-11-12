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
        setup.levelsPath = json.at("levelsPath").get<std::string>();
        setup.menuSelectedFontSize = json.at("menuSelectedFontSize").get<int>();
        setup.menuUnselectedFontSize = json.at("menuUnselectedFontSize").get<int>();
        setup.menuLineHeight = json.at("menuLineHeight").get<int>();
        setup.menuSelectedColor = {
            json.at("menuSelectedColor").at(0).get<unsigned char>(),
            json.at("menuSelectedColor").at(1).get<unsigned char>(),
            json.at("menuSelectedColor").at(2).get<unsigned char>(),
            json.at("menuSelectedColor").at(3).get<unsigned char>()
        };
        setup.menuUnselectedColor = {
            json.at("menuUnselectedColor").at(0).get<unsigned char>(),
            json.at("menuUnselectedColor").at(1).get<unsigned char>(),
            json.at("menuUnselectedColor").at(2).get<unsigned char>(),
            json.at("menuUnselectedColor").at(3).get<unsigned char>()
        };
    } catch (const nlohmann::json::exception& error) {
        std::cerr << "Failed to parse game setup: " << error.what() << "\n";
        UnloadFileText(text);
        return false;
    }

    UnloadFileText(text);
    return true;
}
