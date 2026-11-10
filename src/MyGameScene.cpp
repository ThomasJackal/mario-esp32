#include "MyGameScene.h"
#include "EDGE.h"
#include "World/DemoLevel.h"

extern EDGE engine;

void MyGameScene::init() {
    Renderer& r = engine.getRenderer();
    int viewW = r.getWidth();
    int viewH = r.getHeight();

    tileMap.load(DemoLevel::CELLS, DemoLevel::COLS, DemoLevel::ROWS);

    int worldH, originY;
    tileMap.bottomAlign(viewH, worldH, originY);

    camera.setViewSize(viewW, viewH);
    camera.setWorldSize(tileMap.pixelWidth(), worldH);
    camera.setBottomOverhang(TileMap::BOTTOM_CLIP_PX);
    activeCamera = &camera;
    camera.follow(0, 0);

    int groundTop = tileMap.groundTopAt(1);
    float spawnY = (groundTop >= 0)
        ? (float)(originY + groundTop - PlayerActor::SIZE)
        : (float)(viewH / 2 - PlayerActor::SIZE / 2);
    player = new PlayerActor(10.0f, spawnY);
    addEntity(player);

    tileMap.spawnActors(*this, originY);
}

void MyGameScene::update(unsigned long deltaTime) {
    Scene::update(deltaTime);
    camera.follow(player->x + player->width / 2.0f,
                  player->y + player->height / 2.0f);
}

void MyGameScene::drawWorldEntity(Renderer& renderer, Entity* entity, bool cull) {
    Rect box = entity->getHitBox();
    if (cull && !camera.isVisible(box.x, box.y, box.width, box.height)) return;

    float ox = entity->x, oy = entity->y;
    int ow = entity->width, oh = entity->height;

    int sx, sy, w = ow, h = oh;
    camera.worldToScreen(ox, oy, sx, sy);
    if (camera.clipRect(sx, sy, w, h)) {
        entity->x = (float)sx;
        entity->y = (float)sy;
        entity->width = w;
        entity->height = h;
        entity->draw(renderer);
    }

    entity->x = ox;
    entity->y = oy;
    entity->width = ow;
    entity->height = oh;
}

void MyGameScene::draw(Renderer& renderer) {
    int count = entities.itemCount();
    for (int i = 0; i < count; i++) {
        Entity* entity = entities.dequeue();
        if (entity != player) {
            drawWorldEntity(renderer, entity, true);
        }
        entities.enqueue(entity);
    }
    drawWorldEntity(renderer, player, false);
}
