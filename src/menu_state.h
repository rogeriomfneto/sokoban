#pragma once

#include "game_state.h"

class MenuItem {
    public:
        const char* text;
        GameState* (*onSelectFn)();

        GameState* onSelect();
};

class MenuState : public GameState {
    public:
        void enter() override;
        GameState* update() override;
        void draw() override;

        MenuItem items[2];
        int itemCount = 2;
        int selectedIndex = 0;
};
