#include "menu_state.h"
#include "game_setup.h"
#include "play_state.h"
#include <raylib.h>

GameState* MenuItem::onSelect() {
    return onSelectFn();
}

static GameState* startGame() {
    return new PlayState("level0");
}

static GameState* quitGame() {
    CloseWindow();
    return nullptr;
}

void MenuState::enter() {
    selectedIndex = 0;
    items[0] = {"Start", startGame};
    items[1] = {"Quit", quitGame};
}

GameState* MenuState::update() {
    if (IsKeyPressed(KEY_UP))
        selectedIndex = (selectedIndex - 1 + itemCount) % itemCount;

    if (IsKeyPressed(KEY_DOWN))
        selectedIndex = (selectedIndex + 1) % itemCount;

    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
        return items[selectedIndex].onSelect();

    return nullptr;
}

void MenuState::draw() {
    GameSetup& setup = getGameSetup();
    const int selectedFontSize = 40;
    const int unselectedFontSize = 32;
    const int lineHeight = 48;
    const int startY = (setup.screenHeight - itemCount * lineHeight) / 2;

    BeginDrawing();
    ClearBackground(BLACK);

    for (int i = 0; i < itemCount; i++) {
        bool selected = i == selectedIndex;
        int fontSize = selected ? selectedFontSize : unselectedFontSize;
        Color color = selected ? WHITE : GRAY;
        int textWidth = MeasureText(items[i].text, fontSize);
        int x = (setup.screenWidth - textWidth) / 2;
        int y = startY + i * lineHeight + (lineHeight - fontSize) / 2;

        DrawText(items[i].text, x, y, fontSize, color);
        if (selected)
            DrawText(items[i].text, x + 1, y, fontSize, color);
    }

    EndDrawing();
}
