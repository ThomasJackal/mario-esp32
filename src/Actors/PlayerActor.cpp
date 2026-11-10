#include "PlayerActor.h"
#include "../Managers/KeyboardManager.h"
#include "../World/Camera.h"

PlayerActor::PlayerActor(float x, float y): Actor(x, y, SIZE, SIZE) {
    setCollisionLayer(Layers::PLAYER);
    setCollisionMask(Layers::SOLID | Layers::ENEMY);
}

void PlayerActor::update(unsigned long deltaTime) {
    PlayerInput in;
    in.left = KeyboardManager.GetKey("LEFT");
    in.right = KeyboardManager.GetKey("RIGHT");
    in.jumpPressed = KeyboardManager.GetKeyDown("B");
    in.jumpHeld = KeyboardManager.GetKey("B");
    in.sprint = KeyboardManager.GetKey("A");

    int worldW = activeCamera ? activeCamera->worldW : 0;
    int worldH = activeCamera ? activeCamera->worldH : 0;

    physics.step(x, y, width, height, worldW, worldH, in, deltaTime);
}

void PlayerActor::draw(Renderer& renderer) {
    renderer.drawFilledRectangle((int)x, (int)y, width, height);
}

void PlayerActor::onCollision(Actor* other) {
    // Le moteur ne fait que *notifier* la collision : c'est au joueur de se
    // repousser hors des blocs SOLID (empecher de traverser).
    if (!other->isInLayer(Layers::SOLID)) return;

    // Penetration (AABB) de chaque cote du joueur.
    float overlapLeft   = (x + width)                - other->x;
    float overlapRight  = (other->x + other->width)  - x;
    float overlapTop    = (y + height)               - other->y;
    float overlapBottom = (other->y + other->height) - y;

    // Plus petite penetration sur chaque axe.
    float absX = (overlapLeft < overlapRight) ? overlapLeft : overlapRight;
    float absY = (overlapTop  < overlapBottom) ? overlapTop  : overlapBottom;

    if (absX < absY) {
        if (overlapLeft < overlapRight) x -= overlapLeft;
        else                            x += overlapRight;
        physics.vx = 0.0f;
    } else {
        bool fromAbove = (physics.vy >= 0.0f) ||
                         (y + height * 0.5f <= other->y + other->height * 0.5f);
        if (fromAbove) {
            y -= overlapTop;
            physics.onGround = true;
        } else {
            y += overlapBottom;
        }
        physics.vy = 0.0f;
    }
}
