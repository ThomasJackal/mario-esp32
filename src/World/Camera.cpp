#include "Camera.h"

Camera* activeCamera = nullptr;

void Camera::setViewSize(int w, int h) {
    viewW = w;
    viewH = h;
}

void Camera::setWorldSize(int w, int h) {
    worldW = w;
    worldH = h;
}

void Camera::setBottomOverhang(int px) {
    bottomOverhang = (px > 0) ? px : 0;
}

void Camera::follow(float targetX, float /*targetY*/) {
    camX = targetX - viewW / 2.0f;
    float maxX = (float)(worldW - viewW);
    if (maxX < 0.0f) maxX = 0.0f;
    if (camX < 0.0f) camX = 0.0f;
    if (camX > maxX) camX = maxX;

    // Bas du monde sous le bas de l'ecran de bottomOverhang px.
    float maxY = (float)(worldH - viewH);
    if (maxY < 0.0f) maxY = 0.0f;
    camY = maxY - (float)bottomOverhang;
    if (camY < 0.0f) camY = 0.0f;
}

void Camera::worldToScreen(float wx, float wy, int& sx, int& sy) const {
    sx = (int)(wx - camX);
    sy = (int)(wy - camY);
}

bool Camera::isVisible(float x, float y, int w, int h) const {
    return !(x + w <= camX || x >= camX + viewW ||
             y + h <= camY || y >= camY + viewH);
}

bool Camera::clipRect(int& x, int& y, int& w, int& h) const {
    if (w <= 0 || h <= 0) return false;

    int x2 = x + w;
    int y2 = y + h;

    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x2 > viewW) x2 = viewW;
    if (y2 > viewH) y2 = viewH;

    w = x2 - x;
    h = y2 - y;
    return w > 0 && h > 0;
}
