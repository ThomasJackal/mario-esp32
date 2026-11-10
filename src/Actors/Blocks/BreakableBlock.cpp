#include "BreakableBlock.h"

BreakableBlock::BreakableBlock(float x, float y): BlockActor(x, y) {}

void BreakableBlock::draw(Renderer& renderer) {
    if (broken) return;

    BlockActor::draw(renderer);

    int px = (int)x;
    int py = (int)y;
    renderer.drawLine(px, py + height / 2, px + width - 1, py + height / 2);
    renderer.drawLine(px + width / 2, py, px + width / 2, py + height - 1);
}

void BreakableBlock::onHitFromBelow(Actor* other) {
    broken = true;
    setCollisionLayer(DefaultLayers::kNone);
    setCollisionMask(DefaultLayers::kNone);
}
