#include "UnbreakableBlock.h"

UnbreakableBlock::UnbreakableBlock(float x, float y, int w, int h)
    : BlockActor(x, y, w, h) {}

void UnbreakableBlock::draw(Renderer& renderer) {
    renderer.drawFilledRectangle((int)x, (int)y, width, height);
}
