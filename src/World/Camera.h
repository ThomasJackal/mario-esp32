#pragma once

// Service de scène : suit une cible, convertit monde -> écran, cull le hors-champ.
class Camera {
public:
    float camX = 0.0f;
    float camY = 0.0f;
    int viewW = 0;
    int viewH = 0;
    int worldW = 0;
    int worldH = 0;
    // Decale le pin bas : le bas du monde depasse de N px sous l'ecran
    // (rangee de sol legerement "mangee" par le rebord).
    int bottomOverhang = 0;

    void setViewSize(int w, int h);
    void setWorldSize(int w, int h);
    void setBottomOverhang(int px);

    // Suit le joueur en X. camY epingle le bas du monde sous l'ecran.
    void follow(float targetX, float targetY);

    void worldToScreen(float wx, float wy, int& sx, int& sy) const;
    bool isVisible(float x, float y, int w, int h) const;
    bool clipRect(int& x, int& y, int& w, int& h) const;
};

extern Camera* activeCamera;
