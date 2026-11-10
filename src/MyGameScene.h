#pragma once
#include "Scene.h"
#include "Actors/PlayerActor.h"
#include "World/Camera.h"
#include "World/TileMap.h"

class MyGameScene : public Scene {
public:
    void init() override;
    void update(unsigned long deltaTime) override;
    void draw(Renderer& renderer) override;

private:
    void drawWorldEntity(Renderer& renderer, Entity* entity, bool cull);

    Camera camera;
    TileMap tileMap;
    PlayerActor* player;
};
