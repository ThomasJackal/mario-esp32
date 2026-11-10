#include "TileMap.h"
#include "../Actors/Blocks/BreakableBlock.h"
#include "../Actors/Blocks/UnbreakableBlock.h"

void TileMap::load(const uint8_t* cells, int cols, int rows, int tileSize) {
    _cells = cells;
    _cols = cols;
    _rows = rows;
    _tileSize = tileSize;
}

TileId TileMap::at(int tx, int ty) const {
    if (!_cells || tx < 0 || ty < 0 || tx >= _cols || ty >= _rows) {
        return TILE_EMPTY;
    }
    return static_cast<TileId>(_cells[ty * _cols + tx]);
}

int TileMap::groundTopAt(int tx) const {
    for (int ty = _rows - 1; ty >= 0; ty--) {
        TileId id = at(tx, ty);
        if (id == TILE_SOLID || id == TILE_BREAKABLE) {
            return ty * _tileSize;
        }
    }
    return -1;
}

void TileMap::bottomAlign(int viewH, int& worldH, int& originY) const {
    int mapH = pixelHeight();
    worldH = mapH;
    if (worldH < viewH + BOTTOM_CLIP_PX) {
        worldH = viewH + BOTTOM_CLIP_PX;
    }
    originY = worldH - mapH;
}

void TileMap::spawnActors(Scene& scene, int originY) const {
    if (!_cells) return;

    for (int ty = 0; ty < _rows; ty++) {
        int tx = 0;
        while (tx < _cols) {
            TileId id = at(tx, ty);

            if (id == TILE_EMPTY) {
                tx++;
                continue;
            }

            float px = (float)(tx * _tileSize);
            float py = (float)(originY + ty * _tileSize);

            if (id == TILE_BREAKABLE) {
                scene.addEntity(new BreakableBlock(px, py));
                tx++;
                continue;
            }

            int run = 1;
            while (tx + run < _cols && at(tx + run, ty) == TILE_SOLID) {
                run++;
            }
            scene.addEntity(new UnbreakableBlock(
                px, py, run * _tileSize, _tileSize));
            tx += run;
        }
    }
}
