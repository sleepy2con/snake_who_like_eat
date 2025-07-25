#ifndef CONSTANT_H
#define CONSTANT_H

constexpr int TILE_SIZE = 10;
constexpr int SCALE_UNIT_SIZE = 50;
constexpr int WIDTH_RATIO = 16;
constexpr int HEIGHT_RATIO = 9;

enum class GameObjectsData {
    GD_Type = 0
};

enum class GameObjectTypes {
    GO_Food,
    GO_Wall
};

#endif // CONSTANT_H
