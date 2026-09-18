#include <raylib.h>
#include <raymath.h>

const int windowWidth = 1280;
const int windowHeight = 720;

const int gridCols = 10;
const int gridLines = 5;
const int cellSize = 100;

const int gridWidth = gridCols * cellSize;
const int gridHeight = gridLines * cellSize;

const int xOffset = (windowWidth - gridWidth) / 2;
const int yOffset = (windowHeight - gridHeight) / 2;

typedef struct {
    Vector2 pos;
} Player;


void update(Player &player);
void draw(Player player);

int main(void) {
    InitWindow(1280, 720, "Sokoban");
    SetTargetFPS(60);

    Player player = {{xOffset + cellSize/2, yOffset + cellSize/2}};


    while (!WindowShouldClose())
    {
        update(player);
        draw(player);
    }

    CloseWindow();

    return 0;
}

void update(Player &player) {
    if (IsKeyPressed(KEY_RIGHT)) player.pos.x += cellSize;
    if (IsKeyPressed(KEY_LEFT)) player.pos.x -= cellSize;
    if (IsKeyPressed(KEY_UP)) player.pos.y -= cellSize;
    if (IsKeyPressed(KEY_DOWN)) player.pos.y += cellSize;

    player.pos.x = Clamp(player.pos.x, xOffset + cellSize/2, xOffset + cellSize/2 + (gridCols - 1) * cellSize);
    player.pos.y = Clamp(player.pos.y, yOffset + cellSize/2, yOffset + cellSize/2 + (gridLines - 1) * cellSize);

}

void draw(Player player) {
    BeginDrawing();
    ClearBackground(BLACK);

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
    DrawCircle(player.pos.x, player.pos.y, 40, YELLOW);

    EndDrawing();
}