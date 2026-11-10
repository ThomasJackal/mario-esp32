#include "BlockActor.h"

BlockActor::BlockActor(float x, float y, int w, int h): Actor(x, y, w, h) {
    setCollisionLayer(Layers::SOLID);
    setCollisionMask(Layers::PLAYER);
}

void BlockActor::draw(Renderer& renderer) {
    int px = (int)x;
    int py = (int)y;
    int x2 = px + width  - 1;
    int y2 = py + height - 1;

    // Contour du bloc.
    renderer.drawLine(px, py, x2, py);
    renderer.drawLine(px, y2, x2, y2);
    renderer.drawLine(px, py, px, y2);
    renderer.drawLine(x2, py, x2, y2);
}

void BlockActor::onCollision(Actor* other) {
    // Le masque ne laisse passer que le PLAYER. La resolution physique (empecher
    // de traverser) est faite cote joueur ; ici on ne gere que la reaction du
    // bloc a un coup par en dessous.
    //
    // "Par en dessous" = l'autre est plus bas que le bloc : son centre vertical
    // est sous le centre du bloc (vrai avant comme apres la resolution joueur).
    float otherCenterY = other->y + other->height / 2.0f;
    float blockCenterY = y + height / 2.0f;
    if (otherCenterY > blockCenterY) {
        onHitFromBelow(other);
    }
}
