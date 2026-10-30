#include "game.h"
#include "game_setup.h"
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
    GameSetup& setup = getGameSetup();

    BeginDrawing();
    ClearBackground(BLACK);

    for (int y = 0; y < map.height; y++) {
        for (int x = 0; x < map.width; x++) {
            int mapTile = map.layout[y][x];

            if (mapTile == 0)
                continue;

            int localTileId = mapTile - 1;

            int tilesetColumns = map.texture.width / setup.tileSize;

            int tileX = localTileId % tilesetColumns;
            int tileY = localTileId / tilesetColumns;

            Rectangle source = {
                (float)(tileX * setup.tileSize),
                (float)(tileY * setup.tileSize),
                (float)setup.tileSize,
                (float)setup.tileSize
            };

            Rectangle destination = {
                (float)(xOffset + x * setup.screenTileSize),
                (float)(yOffset + y * setup.screenTileSize),
                (float)setup.screenTileSize,
                (float)setup.screenTileSize
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
            (float)(4 * setup.tileSize),
            (float)setup.tileSize,
            (float)setup.tileSize
        };

        Rectangle destination = {
            (float)(xOffset + box.pos.x * setup.screenTileSize),
            (float)(yOffset + box.pos.y * setup.screenTileSize),
            (float)setup.screenTileSize,
            (float)setup.screenTileSize
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
        (float)setup.playerSpriteSize,
        (float)setup.playerSpriteSize
    };

    Rectangle destination = {
        (float)(xOffset + player.pos.x * setup.screenTileSize),
        (float)(yOffset + player.pos.y * setup.screenTileSize),
        (float)setup.screenTileSize,
        (float)setup.screenTileSize
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
