#include "MyGameScene.h"
#include "EDGE.h"
#include "KeyboardManager.h"

extern EDGE engine;

#define PLAYER_SIZE 8

void MyGameScene::init() {
    Renderer& r = engine.getRenderer();
    int screenH = r.getHeight() - 2 * r.getYOffset();

    player = new PlayerActor(10, screenH - PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE);
    addEntity(player);
}

void MyGameScene::update(unsigned long deltaTime) {
    Scene::update(deltaTime);
}

void MyGameScene::draw(Renderer& renderer) {
    // Ligne de sol (bas de la zone visible).
    int screenW = renderer.getWidth()  - 2 * renderer.getXOffset();
    int screenH = renderer.getHeight() - 2 * renderer.getYOffset();
    renderer.drawLine(0, screenH - 1, screenW - 1, screenH - 1);

    Scene::draw(renderer);
}
