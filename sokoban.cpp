#include <raylib.h>
#include <raymath.h>
#include <iostream>

const int windowWidth = 1280;
const int windowHeight = 720;

const int gridCols = 20;
const int gridLines = 10;
const int cellSize = 50;

const int gridWidth = gridCols * cellSize;
const int gridHeight = gridLines * cellSize;

const int xOffset = (windowWidth - gridWidth) / 2;
const int yOffset = (windowHeight - gridHeight) / 2;

using namespace std;

class Player {
    public:
        Vector2 pos = {1, 1};
};

class Map {
    public:
        char layout[gridLines][gridCols] = {
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
        };
};


void update(Player &player, Map map);
void draw(Player player, Map map);

int main(void) {
    InitWindow(1280, 720, "Sokoban");
    SetTargetFPS(60);

    Player player;
    Map map;


    while (!WindowShouldClose())
    {
        update(player, map);
        draw(player, map);
    }

    CloseWindow();

    return 0;
}

void update(Player &player, Map map) {
    if (IsKeyPressed(KEY_RIGHT)) {
        char mapTile = map.layout[(int) player.pos.y][(int) player.pos.x + 1];
        if (mapTile != '#')
            player.pos.x += 1;
    }

    if (IsKeyPressed(KEY_LEFT)) {
        char mapTile = map.layout[(int) player.pos.y][(int) player.pos.x -1];
        if (mapTile != '#')
            player.pos.x -= 1;
    }

    if (IsKeyPressed(KEY_UP)) {
        char mapTile = map.layout[(int) player.pos.y - 1][(int) player.pos.x];
        if (mapTile != '#')
            player.pos.y -= 1;
    }

    if (IsKeyPressed(KEY_DOWN)) {
        char mapTile = map.layout[(int) player.pos.y + 1][(int) player.pos.x];
        if (mapTile != '#')
            player.pos.y += 1;
    }

    player.pos.x = Clamp(player.pos.x, 0, gridCols - 1);
    player.pos.y = Clamp(player.pos.y, 0, gridLines - 1);

}

void draw(Player player, Map map) {
    BeginDrawing();
    ClearBackground(BLACK);

    // draw map
    for (int i = 0; i < gridLines; i++) {
        for (int j = 0; j < gridCols; j++) {
            char mapTile = map.layout[i][j];

            if (mapTile == '#') {
                DrawRectangle(xOffset + j * cellSize, yOffset + i * cellSize, cellSize, cellSize, GRAY);
            }
        }
    }

    // draws grid
    for (int i = 0; i < gridCols; i++) {
        DrawLine(xOffset + i * cellSize,  yOffset, xOffset + i * cellSize, yOffset + gridHeight, WHITE);    
    }

    DrawLine(xOffset + gridCols * cellSize,  yOffset, xOffset + gridCols * cellSize, yOffset + gridHeight, WHITE);

    for (int i = 0; i < gridLines; i++) {
        DrawLine(xOffset,  yOffset + i * cellSize, xOffset + gridWidth, yOffset + i * cellSize, WHITE);    
    }

    DrawLine(xOffset,  yOffset + gridLines * cellSize, xOffset + gridWidth, yOffset + gridLines * cellSize, WHITE);

    // draws player
    DrawCircle(xOffset + cellSize/2 + player.pos.x * cellSize, yOffset + cellSize/2 + player.pos.y * cellSize, .8 * (cellSize/2), YELLOW);

    EndDrawing();
}