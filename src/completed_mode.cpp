#include "completed_mode.hpp"
#include "game_setup.hpp"
#include "menu_state.hpp"
#include <raylib.h>
#include <raymath.h>

CompletedMode::CompletedMode() {}

void CompletedMode::enter(Map& map, Player& player) {}

PlayResult CompletedMode::update(Map& map, Player& player) {
    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)) {
        return {nullptr, new MenuState()};
    }

    return {nullptr, nullptr};
}

void CompletedMode::draw(Map& map, Player& player) {
    GameSetup& setup = getGameSetup();

    int headerLineHeight = setup.menuLineHeight * 2;
    int headerFontSize = setup.menuSelectedFontSize * 2;
    int captionLineHeight = setup.menuLineHeight;
    int captionFontSize = setup.menuUnselectedFontSize;
    
    int headerWidth = MeasureText(setup.completedHeaderText.c_str(), headerFontSize);
    int captionWidth = MeasureText(setup.completedCaptionText.c_str(), captionFontSize);

    const int startY = (setup.screenHeight - headerLineHeight - captionLineHeight) / 2;

    BeginDrawing();
    ClearBackground(BLACK);

    int x = (setup.screenWidth - headerWidth) / 2;
    int y = startY;

    DrawText(setup.completedHeaderText.c_str(), x, y, headerFontSize, setup.menuSelectedColor);

    x = (setup.screenWidth - captionWidth) / 2;
    y = startY + headerLineHeight;

    DrawText(setup.completedCaptionText.c_str(), x, y, captionFontSize, setup.menuUnselectedColor);

    EndDrawing();
}


