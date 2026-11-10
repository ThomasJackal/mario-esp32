#pragma once
#include "Actor.h"
#include "../../GameLayers.h"

// Classe de base de tous les blocs (brique, bloc mystere, tuyau...).
// Un bloc est un Actor SOLID : il bloque physiquement le joueur. La reaction
// a un coup "par en dessous" est centralisee ici et deleguee aux sous-classes
// via onHitFromBelow().
class BlockActor : public Actor {
public:
    static constexpr int SIZE = 8;  // taille par defaut d'un bloc (px)

    BlockActor(float x, float y, int w = SIZE, int h = SIZE);

    void update(unsigned long deltaTime) override {}
    void draw(Renderer& renderer) override;

    Rect getHitBox() override { return {x, y, width, height}; }
    void onCollision(Actor* other) override;
    void onCollision(Entity* other) override {}

protected:
    // Appelee quand un Actor frappe le bloc par en dessous (joueur qui saute).
    virtual void onHitFromBelow(Actor* other) {}
};
