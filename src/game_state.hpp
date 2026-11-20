#pragma once

class GameState {
    public:
        virtual ~GameState() = default;
        virtual void enter() = 0;
        virtual GameState* update() = 0;
        virtual void draw() = 0;
};
