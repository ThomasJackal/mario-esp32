#pragma once
#include "Actor.h"
#include "../GameLayers.h"
#include "../Managers/PlayerPhysicsManager.h"

class PlayerActor : public Actor {
public:
    PlayerPhysicsManager physics;

    PlayerActor(float x, float y, int w, int h);

    void update(unsigned long deltaTime) override;
    void draw(Renderer& renderer) override;

    Rect getHitBox() override { return {x, y, width, height}; }
    void onCollision(Actor* other) override;

    void onCollision(Entity* other) override {}
};
