#include "EDGE.h"
#include "src/MyGameScene.h"
#include "src/Managers/KeyboardManager.h"

#define I2C_SDA 18
#define I2C_SCL 17
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 46

DisplayConfig config(SSD1306, U8G2_R0, I2C_SCL, I2C_SDA, U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE, SCREEN_WIDTH, SCREEN_HEIGHT, true);
EDGE engine(config);
MyGameScene gameScene;

void setup() {
    Serial.begin(115200);
    KeyboardManager.begin("decode-etudiants", "learnByDoing25!", IPAddress(192, 168, 191, 148), 10000);

    engine.init();
    engine.setScene(&gameScene);
}

void loop() {
    KeyboardManager.update();
    engine.update();
    engine.draw();
}
