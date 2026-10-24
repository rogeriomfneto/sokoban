#include "game.h"
#include "constants.h"
#include <raylib.h>
#include <raymath.h>

void update(Player& player, Map& map) {
    if (IsKeyPressed(KEY_RIGHT))
        player.tryMove(map, Direction::Right);

    if (IsKeyPressed(KEY_LEFT))
        player.tryMove(map, Direction::Left);

    if (IsKeyPressed(KEY_UP))
        player.tryMove(map, Direction::Up);

    if (IsKeyPressed(KEY_DOWN))
        player.tryMove(map, Direction::Down);

    player.pos.x = Clamp(player.pos.x, 0, map.width - 1);
    player.pos.y = Clamp(player.pos.y, 0, map.height - 1);
}

void draw(Player player, Map map, int xOffset, int yOffset) {
    BeginDrawing();
    ClearBackground(BLACK);

    for (int y = 0; y < map.height; y++) {
        for (int x = 0; x < map.width; x++) {
            int mapTile = map.layout[y][x];

            if (mapTile == 0)
                continue;

            int localTileId = mapTile - 1;

            int tilesetColumns = map.texture.width / TILE_SIZE;

            int tileX = localTileId % tilesetColumns;
            int tileY = localTileId / tilesetColumns;

            Rectangle source = {
                (float)(tileX * TILE_SIZE),
                (float)(tileY * TILE_SIZE),
                (float)TILE_SIZE,
                (float)TILE_SIZE
            };

            Rectangle destination = {
                (float)(xOffset + x * SCREEN_TILE_SIZE),
                (float)(yOffset + y * SCREEN_TILE_SIZE),
                (float)SCREEN_TILE_SIZE,
                (float)SCREEN_TILE_SIZE
            };

            DrawTexturePro(
                map.texture,
                source,
                destination,
                {0, 0},
                0,
                WHITE
            );
        }
    }

    for (int i = 0; i < map.boxCount; i++) {
        Box box = map.boxes[i];

        Rectangle source = {
            0.0f,
            (float)(4 * TILE_SIZE),
            (float)TILE_SIZE,
            (float)TILE_SIZE
        };

        Rectangle destination = {
            (float)(xOffset + box.pos.x * SCREEN_TILE_SIZE),
            (float)(yOffset + box.pos.y * SCREEN_TILE_SIZE),
            (float)SCREEN_TILE_SIZE,
            (float)SCREEN_TILE_SIZE
        };

        DrawTexturePro(
            map.texture,
            source,
            destination,
            {0, 0},
            0,
            WHITE
        );
    }

    Rectangle source = {
        0.0f,
        0.0f,
        (float)PLAYER_SPRITE_SIZE,
        (float)PLAYER_SPRITE_SIZE
    };

    Rectangle destination = {
        (float)(xOffset + player.pos.x * SCREEN_TILE_SIZE),
        (float)(yOffset + player.pos.y * SCREEN_TILE_SIZE),
        (float)SCREEN_TILE_SIZE,
        (float)SCREEN_TILE_SIZE
    };

    DrawTexturePro(
        player.texture,
        source,
        destination,
        {0, 0},
        0,
        WHITE
    );

    EndDrawing();
}
