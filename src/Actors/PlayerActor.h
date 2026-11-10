#pragma once
#include "Actor.h"
#include "../GameLayers.h"
#include "../Managers/PlayerPhysicsManager.h"

class PlayerActor : public Actor {
public:
    static constexpr int SIZE = 8;  // taille du joueur (px)

    PlayerPhysicsManager physics;

    PlayerActor(float x, float y);

    void update(unsigned long deltaTime) override;
    void draw(Renderer& renderer) override;

    Rect getHitBox() override { return {x, y, width, height}; }
    void onCollision(Actor* other) override;

    void onCollision(Entity* other) override {}
};
