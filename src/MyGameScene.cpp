#include "MyGameScene.h"
#include "EDGE.h"
#include "Managers/KeyboardManager.h"

extern EDGE engine;

void MyGameScene::init() {
    Renderer& r = engine.getRenderer();
    int screenH = r.getHeight() - 2 * r.getYOffset();

    // Chaque Actor connait sa propre taille : la scene ne fait que le placer.
    player = new PlayerActor(10, screenH - PlayerActor::SIZE);
    addEntity(player);

    // Bloc cassable en suspension : le joueur peut sauter dessous pour le casser.
    block = new BreakableBlock(40, screenH - 3 * BlockActor::SIZE);
    addEntity(block);
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
