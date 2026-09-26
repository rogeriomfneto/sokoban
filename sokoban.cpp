#include <iostream>
#include <cstdint>
#include <algorithm>
#include <raylib.h>
#include <raymath.h>
#include <tileson.hpp>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int TILE_SIZE = 16;
const int PLAYER_SPRITE_SIZE = 16;
const int SCREEN_TILE_SIZE = 50;

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
        int layout[50][50];

        int width = 0;
        int height = 0;

        Texture2D texture; 

        Box boxes[50];
        int boxCount = 0;

        void loadMap(tson::Map& tileson) {
            width = tileson.getSize().x;
            height = tileson.getSize().y;
            auto& layer = tileson.getLayers()[0];

            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    int index = y * width + x;
                    int gid = layer.getData()[index];
                    layout[y][x] = gid;
                }
            }
        }

        bool isWall(int x, int y) {
            return layout[y][x] == 1 || layout[y][x] == 2 || layout[y][x] == 3;
        }

        bool isEmpty(int x, int y) {
            return layout[y][x] == 6 || layout[y][x] == 4 || layout[y][x] == 7;
        }

        bool isButton(int x, int y) {
            return layout[y][x] == 4;
        }

        void loadBoxes(Box newBoxes[], int n) {
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
            

            if (layout[(int) pos.y][(int) pos.x] == 4) box->inPlace = true;
            else box->inPlace = false;

        }

        bool canMoveBox(Box box, Direction direction) {
            Vector2 pos = applyDirectionToPosition(box.pos, direction);
            int x = pos.x; int y = pos.y;

            if (!isEmpty(pos.x, pos.y) || getBox(x, y) != nullptr) return false;

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
        Vector2 pos = {0, 0};
        Texture2D texture;

        void tryMove(Map &map, Direction direction) {
            Vector2 newPos = applyDirectionToPosition(pos, direction);
            int x = newPos.x; int y = newPos.y;

            if (map.isWall(x, y)) return; 

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
void draw(Player player, Map map,  int xOffset, int yOffset);

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sokoban");
    SetTargetFPS(60);

    Texture2D tilesetTexture = LoadTexture("assets/tilesets/map.png");
    Texture2D playerTexture = LoadTexture("assets/sprites/player-idle.png");
    
    Map map;
    tson::Tileson parser;

    std::unique_ptr<tson::Map> tilesonMap = parser.parse("assets/levels/level0.tmj");

    if (!tilesonMap || tilesonMap->getStatus() != tson::ParseStatus::OK)
    {
        std::cout << "Failed to load map\n";
        return 1;
    }

    map.loadMap(*tilesonMap);

    Box boxes[] = {
        {4, 4},
        {3, 2},
        {4, 8},
        {8, 8}
    };

    map.loadBoxes(boxes, 4);
    map.texture = tilesetTexture;

    Player player = {{map.width/2, map.height/2}, playerTexture};

    const int xOffset = (SCREEN_WIDTH - map.width * SCREEN_TILE_SIZE) / 2;
    const int yOffset = (SCREEN_HEIGHT - map.height * SCREEN_TILE_SIZE) / 2;

    while (!WindowShouldClose())
    {
        update(player, map);
        draw(player, map, xOffset, yOffset);
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

    player.pos.x = Clamp(player.pos.x, 0, map.width - 1);
    player.pos.y = Clamp(player.pos.y, 0, map.height - 1);

}

void draw(Player player, Map map, int xOffset, int yOffset) {
    BeginDrawing();
    ClearBackground(BLACK);

    // draw map
    for (int y = 0; y < map.height; y++) {
        for (int x = 0; x < map.width; x++) {
            int mapTile = map.layout[y][x];

            if (mapTile == 0)
                continue;

            int localTileId = mapTile - 1;

            int tilesetColumns = map.texture.width / TILE_SIZE;

            int tileX = localTileId % tilesetColumns;
            int tileY = localTileId / tilesetColumns;

            Rectangle source =
            {
                tileX * TILE_SIZE,
                tileY * TILE_SIZE,
                TILE_SIZE,
                TILE_SIZE
            };

            Rectangle destination =
            {
                xOffset + x * SCREEN_TILE_SIZE,
                yOffset + y * SCREEN_TILE_SIZE,
                SCREEN_TILE_SIZE,
                SCREEN_TILE_SIZE
            };

            DrawTexturePro(
                map.texture,
                source,
                destination,
                { 0, 0 },
                0,
                WHITE
            );

        }
    }

    // draws boxes
    for (int i = 0; i < map.boxCount; i++) {
        Box box = map.boxes[i];

        Rectangle source =
        {
            0 * TILE_SIZE,
            4 * TILE_SIZE,
            TILE_SIZE,
            TILE_SIZE
        };

        Rectangle destination =
        {
            xOffset + box.pos.x * SCREEN_TILE_SIZE,
            yOffset + box.pos.y * SCREEN_TILE_SIZE,
            SCREEN_TILE_SIZE,
            SCREEN_TILE_SIZE
        };

        DrawTexturePro(
            map.texture,
            source,
            destination,
            { 0, 0 },
            0,
            WHITE
        );

    }


    // draws player
    Rectangle source =
        {
            0,
            0,
            PLAYER_SPRITE_SIZE,
            PLAYER_SPRITE_SIZE
        };

        Rectangle destination =
        {
            xOffset + player.pos.x * SCREEN_TILE_SIZE,
            yOffset + player.pos.y * SCREEN_TILE_SIZE,
            SCREEN_TILE_SIZE,
            SCREEN_TILE_SIZE
        };

        DrawTexturePro(
            player.texture,
            source,
            destination,
            { 0, 0 },
            0,
            WHITE
        );

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