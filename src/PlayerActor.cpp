#include "PlayerActor.h"
#include "KeyboardManager.h"
#include "EDGE.h"

extern EDGE engine;

PlayerActor::PlayerActor(float x, float y, int w, int h): Actor(x, y, w, h) {
    setCollisionLayer(Layers::PLAYER);
    setCollisionMask(Layers::SOLID | Layers::ENEMY);
}

void PlayerActor::update(unsigned long deltaTime) {
    PlayerInput in;
    in.left = KeyboardManager.GetKey("LEFT");
    in.right = KeyboardManager.GetKey("RIGHT");
    in.jumpPressed = KeyboardManager.GetKeyDown("B");
    in.jumpHeld = KeyboardManager.GetKey("B");

    Renderer& r = engine.getRenderer();
    int worldW = r.getWidth()  - 2 * r.getXOffset();
    int worldH = r.getHeight() - 2 * r.getYOffset();

    physics.step(x, y, width, height, worldW, worldH, in, deltaTime);
}

void PlayerActor::draw(Renderer& renderer) {
    renderer.drawFilledRectangle((int)x, (int)y, width, height);
}

void PlayerActor::onCollision(Actor* other) {
    // Pas encore de plateformes/ennemis : rien à faire.
    // La résolution fine se fera ici quand on ajoutera des Actors SOLID.
}
