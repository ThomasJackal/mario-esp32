#include "PlayerActor.h"
#include "../Managers/KeyboardManager.h"
#include "EDGE.h"

extern EDGE engine;

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

    Renderer& r = engine.getRenderer();
    int worldW = r.getWidth()  - 2 * r.getXOffset();
    int worldH = r.getHeight() - 2 * r.getYOffset();

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

    // On resout sur l'axe de moindre penetration (MTV) et on tue la vitesse
    // correspondante.
    if (absX < absY) {
        if (overlapLeft < overlapRight) x -= overlapLeft;   // bloc a droite
        else                            x += overlapRight;  // bloc a gauche
        physics.vx = 0.0f;
    } else {
        if (overlapTop < overlapBottom) {
            y -= overlapTop;             // on se pose sur le dessus du bloc
            physics.onGround = true;
        } else {
            y += overlapBottom;          // on cogne le bloc par en dessous
        }
        physics.vy = 0.0f;
    }
}
