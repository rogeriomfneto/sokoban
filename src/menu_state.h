#pragma once

#include "game_state.h"
#include <string>

class MenuState;

class MenuItem {
    public:
        std::string text;
        GameState* (*onSelectFn)(MenuState* menu);

        GameState* onSelect(MenuState* menu);
};

class MenuState : public GameState {
    public:
        void enter() override;
        GameState* update() override;
        void draw() override;

        void loadDefaultMenu();
        void loadLevels();

        static const int maxItems = 10;

        MenuItem items[maxItems];
        int itemCount = 0;
        int selectedIndex = 0;
};
