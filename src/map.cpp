#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <tileson.hpp>
#include "map.h"

bool Map::loadFromFile(const char* path) {
    int dataSize = 0;
    unsigned char* fileData = LoadFileData(path, &dataSize);
    if (fileData == nullptr)
        return false;

    auto jsonParser = std::make_unique<tson::Json11>();
    jsonParser->directory(std::filesystem::path(path).parent_path());
    tson::Tileson parser(std::move(jsonParser));

    std::unique_ptr<tson::Map> tilesonMap =
        parser.parse(fileData, static_cast<size_t>(dataSize));
    UnloadFileData(fileData);

    if (!tilesonMap || tilesonMap->getStatus() != tson::ParseStatus::OK)
        return false;

    loadMap(*tilesonMap);
    loadBoxes(*tilesonMap);

    if (spawnPosition.x < 0 || spawnPosition.y < 0)
        return false;

    return true;
}

void Map::loadMap(tson::Map& tileson) {
    width = tileson.getSize().x;
    height = tileson.getSize().y;
    spawnPosition = {-1, -1};

    tson::Layer* floor = tileson.getLayer("Floor");
    if (floor == nullptr)
        return;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = y * width + x;
            int gid = floor->getData()[index];
            layout[y][x] = gid;

            if (gid == 5)
                spawnPosition = {(float)x, (float)y};
        }
    }
}

bool Map::isWall(int x, int y) {
    return layout[y][x] == 1 || layout[y][x] == 2 || layout[y][x] == 3;
}

bool Map::isEmpty(int x, int y) {
    int gid = layout[y][x];
    return gid == 6 || gid == 4 || gid == 7 || gid == 5;
}

bool Map::isButton(int x, int y) {
    return layout[y][x] == 4;
}

void Map::loadBoxes(tson::Map& tileson) {
    boxCount = 0;

    tson::Layer* boxesLayer = tileson.getLayer("Boxes");
    if (boxesLayer == nullptr)
        return;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = y * width + x;
            uint32_t gid = boxesLayer->getData()[index];
            if (gid == 0)
                continue;

            if (boxCount >= 50)
                return;

            boxes[boxCount].pos = {(float)x, (float)y};
            boxes[boxCount].inPlace = layout[y][x] == 4;
            boxCount++;
        }
    }
}

void Map::moveBox(Box* box, Direction direction) {
    Vector2 pos = applyDirectionToPosition((*box).pos, direction);

    box->pos.x = pos.x;
    box->pos.y = pos.y;

    if (layout[(int)pos.y][(int)pos.x] == 4)
        box->inPlace = true;
    else
        box->inPlace = false;
}

bool Map::canMoveBox(Box box, Direction direction) {
    Vector2 pos = applyDirectionToPosition(box.pos, direction);
    int x = pos.x;
    int y = pos.y;

    if (!isEmpty(pos.x, pos.y) || getBox(x, y) != nullptr)
        return false;

    return true;
}

Box* Map::getBox(int x, int y) {
    for (int i = 0; i < boxCount; i++) {
        if ((int)boxes[i].pos.x == x && (int)boxes[i].pos.y == y)
            return &boxes[i];
    }

    return nullptr;
}
