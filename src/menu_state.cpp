#include "menu_state.hpp"
#include "game_setup.hpp"
#include "play_state.hpp"
#include <raylib.h>

GameState* MenuItem::onSelect(MenuState* menu) {
    return onSelectFn(menu);
}

static GameState* startGame(MenuState*) {
    return new PlayState("level1");
}

static GameState* openLevels(MenuState* menu) {
    menu->loadLevels();
    return nullptr;
}

static GameState* quitGame(MenuState*) {
    CloseWindow();
    return nullptr;
}

static GameState* selectLevel(MenuState* menu) {
    return new PlayState(menu->items[menu->selectedIndex].text.c_str());
}

static GameState* backToMenu(MenuState* menu) {
    menu->loadDefaultMenu();
    return nullptr;
}

void MenuState::enter() {
    selectedIndex = 0;
    loadDefaultMenu();
}

void MenuState::loadDefaultMenu() {
    items[0].text = "Start";
    items[0].onSelectFn = startGame;

    items[1].text = "Levels";
    items[1].onSelectFn = openLevels;

    items[2].text = "Quit";
    items[2].onSelectFn = quitGame;

    itemCount = 3;
    selectedIndex = 0;
}

void MenuState::loadLevels() {
    GameSetup& setup = getGameSetup();
    FilePathList files = LoadDirectoryFilesEx(setup.levelsPath.c_str(), ".tmj", false);

    int levelCount = 0;
    int maxLevels = maxItems - 1;

    for (int i = 0; i < files.count; i++) {
        if (levelCount >= maxLevels) {
            break;
        }

        const char* name = GetFileNameWithoutExt(files.paths[i]);
        items[levelCount].text = name;
        items[levelCount].onSelectFn = selectLevel;
        levelCount = levelCount + 1;
    }

    UnloadDirectoryFiles(files);

    items[levelCount].text = "Back";
    items[levelCount].onSelectFn = backToMenu;

    itemCount = levelCount + 1;
    selectedIndex = 0;
}

GameState* MenuState::update() {
    if (IsKeyPressed(KEY_UP))
        selectedIndex = (selectedIndex - 1 + itemCount) % itemCount;

    if (IsKeyPressed(KEY_DOWN))
        selectedIndex = (selectedIndex + 1) % itemCount;

    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
        return items[selectedIndex].onSelect(this);
    }

    return nullptr;
}

void MenuState::draw() {
    GameSetup& setup = getGameSetup();
    const int startY = (setup.screenHeight - itemCount * setup.menuLineHeight) / 2;

    BeginDrawing();
    ClearBackground(BLACK);

    for (int i = 0; i < itemCount; i++) {
        bool selected = i == selectedIndex;
        int fontSize = selected ? setup.menuSelectedFontSize : setup.menuUnselectedFontSize;
        Color color = selected ? setup.menuSelectedColor : setup.menuUnselectedColor;
        int textWidth = MeasureText(items[i].text.c_str(), fontSize);
        int x = (setup.screenWidth - textWidth) / 2;
        int y = startY + i * setup.menuLineHeight + (setup.menuLineHeight - fontSize) / 2;

        DrawText(items[i].text.c_str(), x, y, fontSize, color);
        if (selected)
            DrawText(items[i].text.c_str(), x + 1, y, fontSize, color);
    }

    EndDrawing();
}
