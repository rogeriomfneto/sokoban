#include <iostream>
#include <raylib.h>
#include "game_setup.h"
#include "game_state.h"
#include "menu_state.h"

int main(void) {
    if (!loadGameSetup("assets/game-setup.json")) {
        std::cout << "Failed to load game setup\n";
        return 1;
    }

    GameSetup& setup = getGameSetup();

    InitWindow(setup.screenWidth, setup.screenHeight, "Sokoban");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    GameState* state = new MenuState();
    state->enter();

    while (!WindowShouldClose()) {
        GameState* next = state->update();
        if (next != nullptr) {
            delete state;
            state = next;
            state->enter();
        }
        if (WindowShouldClose())
            break;
        state->draw();
    }

    delete state;
    CloseWindow();

    return 0;
}
