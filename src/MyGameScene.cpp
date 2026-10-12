#include "MyGameScene.h"
#include "EDGE.h"
#include "KeyboardManager.h"

extern EDGE engine;

void MyGameScene::init() {
    // Initialize scene
}

void MyGameScene::update(unsigned long deltaTime) {
    // Game logic
}

void MyGameScene::draw(Renderer& renderer) {
    renderer.drawText(10, 10, "Hello EDGE!");

    if (KeyboardManager.GetKeyDown("A")) { 
        renderer.drawText(0, 0, "A");
    }

    if (KeyboardManager.GetKey("RIGHT")) {
        renderer.drawText(0, 0, "RIGHT");
    }
}