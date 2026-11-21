#include "play_state.hpp"
#include "game_setup.hpp"
#include "running_mode.hpp"
#include <iostream>
#include <raylib.h>
#include <raymath.h>

PlayState::PlayState(const char* levelName) : levelName(levelName) {}

PlayState::~PlayState() {
    UnloadTexture(map.texture);
    UnloadTexture(player.texture);
    delete playMode;
}

void PlayState::enter() {
    GameSetup& setup = getGameSetup();

    std::string path = setup.levelsPath + levelName + ".tmj";
    if (!map.loadFromFile(path.c_str())) {
        std::cout << "Failed to load map\n";
        CloseWindow();
        return;
    }

    map.texture = LoadTexture(setup.tilesetPath.c_str());
    player = {map.spawnPosition, LoadTexture(setup.playerSpritePath.c_str())};

    playMode = new RunningMode();
    playMode->enter(map, player);
}

GameState* PlayState::update() {
    PlayResult result = playMode->update(map, player);

    if (result.nextState != nullptr) {
        return result.nextState;
    }

    if (result.nextMode != nullptr) {
        delete playMode;
        playMode = result.nextMode;
        playMode->enter(map, player);
    }

    return nullptr;
}

void PlayState::draw() {
    playMode->draw(map, player);
}
