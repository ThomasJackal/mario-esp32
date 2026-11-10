#pragma once
#include "BlockActor.h"

// Bloc solide indestructible (sol, mur, plateforme).
// Peut etre plus large/haut qu'une tuile (runs fusionnes par la TileMap).
class UnbreakableBlock : public BlockActor {
public:
    UnbreakableBlock(float x, float y, int w = SIZE, int h = SIZE);

    void draw(Renderer& renderer) override;

protected:
    // Pas de reaction au coup par en dessous.
    void onHitFromBelow(Actor* other) override {}
};
