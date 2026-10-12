#pragma once
#include "Scene.h"
#include "Actors/PlayerActor.h"

class MyGameScene : public Scene {
public:
    void init() override;
    void update(unsigned long deltaTime) override;
    void draw(Renderer& renderer) override;

private:
    PlayerActor* player;
};
