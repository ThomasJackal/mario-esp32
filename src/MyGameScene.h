#pragma once
#include "Scene.h"

class MyGameScene : public Scene {
public:
    void init() override;
    void update(unsigned long deltaTime) override;
    void draw(Renderer& renderer) override;
};