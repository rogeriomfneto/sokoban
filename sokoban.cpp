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

enum class Direction {
    Up,
    Down,
    Left,
    Right
};

Vector2 applyDirectionToPosition(Vector2 pos, Direction direction);

class Box {
    public:
        Vector2 pos = {2, 2};
        bool inPlace = false;
};

class Map {
    public:
        char layout[gridLines][gridCols] = {
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', '.', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '.', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', '.', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '.', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
        };

        Box boxes[100];
        int boxCount = 0;

        void placeBoxes(Box newBoxes[], int n) {
            boxCount = n;

            for (int i = 0; i < n; i++) {
                Box box = newBoxes[i];
                boxes[i] = box;
            }
        }

        void moveBox(Box* box, Direction direction) {
            Vector2 pos = applyDirectionToPosition((*box).pos, direction);

            box->pos.x = pos.x;
            box->pos.y = pos.y;
            

            if (layout[(int) pos.y][(int) pos.x] == '.') box->inPlace = true;
            else box->inPlace = false;

        }

        bool canMoveBox(Box box, Direction direction) {
            Vector2 pos = applyDirectionToPosition(box.pos, direction);
            int x = pos.x; int y = pos.y;

            if (layout[y][x] != ' ' && layout[y][x] != '.' || getBox(x, y) != nullptr) return false;

            return true;
        }

        Box* getBox(int x, int y) {
            for (int i = 0; i < boxCount; i++) {
                if ((int) boxes[i].pos.x == x && (int) boxes[i].pos.y == y) return &boxes[i];
            }

            return nullptr;
        }
};

class Player {
    public:
        Vector2 pos = {5, 5};

        void tryMove(Map &map, Direction direction) {
            Vector2 newPos = applyDirectionToPosition(pos, direction);
            int x = newPos.x; int y = newPos.y;

            if (map.layout[y][x] == '#') return; 

            Box* box = map.getBox(x, y);

            if (box == nullptr) {
                pos.x = x;
                pos.y = y;
                return;
            } 

            if (map.canMoveBox(*box, direction)) {
                map.moveBox(box, direction);
                pos.x = x;
                pos.y = y;
            }
        }
};

void update(Player &player, Map &map);
void draw(Player player, Map map);

int main(void) {
    InitWindow(1280, 720, "Sokoban");
    SetTargetFPS(60);

    Player player = {gridCols/2, gridLines/2};
    Map map;

    Box boxes[] = {
        {4, 4},
        {3, 2},
        {4, 8},
        {8, 8}
    };

    map.placeBoxes(boxes, 4);


    while (!WindowShouldClose())
    {
        update(player, map);
        draw(player, map);
    }

    CloseWindow();

    return 0;
}

void update(Player &player, Map &map) {
    // handle input
    if (IsKeyPressed(KEY_RIGHT)) {
        player.tryMove(map, Direction::Right);
    }

    if (IsKeyPressed(KEY_LEFT)) {
        player.tryMove(map, Direction::Left);
    }

    if (IsKeyPressed(KEY_UP)) {
        player.tryMove(map, Direction::Up);
    }

    if (IsKeyPressed(KEY_DOWN)) {
        player.tryMove(map, Direction::Down);
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

            if (mapTile == '.') {
                DrawCircle(xOffset + cellSize/2 + j * cellSize, yOffset + cellSize/2 + i * cellSize, .1 * (cellSize/2), RED);
            }
        }
    }

    // draws boxes
    for (int i = 0; i < map.boxCount; i++) {
        Box box = map.boxes[i];
        Color boxColor = box.inPlace ? YELLOW : BROWN;
        DrawRectangle(xOffset + box.pos.x * cellSize, yOffset + box.pos.y * cellSize, cellSize, cellSize, boxColor);
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
    DrawCircle(xOffset + cellSize/2 + player.pos.x * cellSize, yOffset + cellSize/2 + player.pos.y * cellSize, .8 * (cellSize/2), BLUE);

    EndDrawing();
}

Vector2 applyDirectionToPosition(Vector2 pos, Direction direction) {
    if (direction == Direction::Up) {
        return {pos.x, pos.y - 1};
    } else if (direction == Direction::Down) {
        return {pos.x, pos.y + 1};
    } else if (direction == Direction::Left) {
        return {pos.x - 1, pos.y};
    } else {
        return {pos.x + 1, pos.y};
    }
}