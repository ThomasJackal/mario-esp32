#pragma once
#include "BlockActor.h"

// Brique cassable : disparait quand le joueur la frappe par en dessous.
class BreakableBlock : public BlockActor {
public:
    BreakableBlock(float x, float y);

    void draw(Renderer& renderer) override;

    bool isBroken() const { return broken; }

protected:
    void onHitFromBelow(Actor* other) override;

private:
    bool broken = false;
};
