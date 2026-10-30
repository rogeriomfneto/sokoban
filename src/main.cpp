#include <iostream>
#include <raylib.h>
#include "game.h"
#include "game_setup.h"
#include "map.h"
#include "player.h"

int main(void) {
    if (!loadGameSetup("assets/game-setup.json")) {
        std::cout << "Failed to load game setup\n";
        return 1;
    }

    GameSetup& setup = getGameSetup();

    InitWindow(setup.screenWidth, setup.screenHeight, "Sokoban");
    SetTargetFPS(60);

    Texture2D tilesetTexture = LoadTexture("assets/tilesets/map.png");
    Texture2D playerTexture = LoadTexture("assets/sprites/player-idle.png");

    Map map;
    if (!map.loadFromFile("assets/levels/level0.tmj")) {
        std::cout << "Failed to load map\n";
        return 1;
    }

    map.texture = tilesetTexture;

    Player player = {map.spawnPosition, playerTexture};

    const int xOffset = (setup.screenWidth - map.width * setup.screenTileSize) / 2;
    const int yOffset = (setup.screenHeight - map.height * setup.screenTileSize) / 2;

    while (!WindowShouldClose()) {
        update(player, map);
        draw(player, map, xOffset, yOffset);
    }

    CloseWindow();

    return 0;
}
