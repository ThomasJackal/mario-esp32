#pragma once
#include <Arduino.h>
#include "Scene.h"

enum TileId : uint8_t {
    TILE_EMPTY     = 0,
    TILE_SOLID     = 1,
    TILE_BREAKABLE = 2,
};

// Grille 2D. Source de verite du niveau + constantes de layout ecran/tuiles.
class TileMap {
public:
    static constexpr int TILE_SIZE = 8;
    static constexpr int BOTTOM_CLIP_PX = 3;  // sol legerement mange par le bas
    static constexpr int MAX_ROWS = 9;        // hauteur max d'un niveau (tuiles)

    static int maxTileRowsOnScreen(int viewH) { return viewH / TILE_SIZE; }

    void load(const uint8_t* cells, int cols, int rows, int tileSize = TILE_SIZE);

    int cols() const { return _cols; }
    int rows() const { return _rows; }
    int tileSize() const { return _tileSize; }
    int pixelWidth() const { return _cols * _tileSize; }
    int pixelHeight() const { return _rows * _tileSize; }

    TileId at(int tx, int ty) const;
    int groundTopAt(int tx) const;

    // worldH / originY pour coller la map en bas + BOTTOM_CLIP_PX sous l'ecran.
    void bottomAlign(int viewH, int& worldH, int& originY) const;

    void spawnActors(Scene& scene, int originY = 0) const;

private:
    const uint8_t* _cells = nullptr;
    int _cols = 0;
    int _rows = 0;
    int _tileSize = TILE_SIZE;
};
