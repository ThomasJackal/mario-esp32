#include "EDGE.h"
#include "src/MyGameScene.h"
#include "src/Managers/KeyboardManager.h"

#define I2C_SDA 18
#define I2C_SCL 17
// Buffer SSD1306 natif — pas de "fenetre" 46px centree (sinon marges mortes
// haut/bas que la camera clippe avant le vrai rebord OLED).
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

DisplayConfig config(SSD1306, U8G2_R0, I2C_SCL, I2C_SDA, U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE, SCREEN_WIDTH, SCREEN_HEIGHT, true);
EDGE engine(config);
MyGameScene gameScene;

void setup() {
    Serial.begin(115200);
    //hotspot
    KeyboardManager.begin("honor-7x", "ab403679356f$¿A", IPAddress(192, 168, 43, 174), 10000);
    //decode
    //KeyboardManager.begin("decode-etudiants", "learnByDoing25!", IPAddress(192, 168, 191, 60), 10000);

    engine.init();
    // EDGE ne copie pas DisplayConfig dans Renderer.width/height (defaut 128x64)
    // ni ne garantit offset 0 si la config change : on aligne explicitement.
    engine.getRenderer().setDisplaySize(SCREEN_WIDTH, SCREEN_HEIGHT);
    engine.getRenderer().setDisplayOffset(0, 0);
    engine.setScene(&gameScene);
}

void loop() {
    KeyboardManager.update();
    engine.update();
    engine.draw();
}
