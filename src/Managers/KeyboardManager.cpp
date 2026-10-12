#include "KeyboardManager.h"

KeyboardManagerClass KeyboardManager;

void KeyboardManagerClass::begin(const char* ssid, const char* password, IPAddress host, uint16_t port) {
    _host = host;
    _port = port;

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println(WiFi.status());
    }
    Serial.print("WiFi connected with IP:");
    Serial.println(WiFi.localIP());
}

void KeyboardManagerClass::update() {
    _prev = _held;

    if (!_client.connected()) {
        _client.connect(_host, _port);
    }

    while (_client.available()) {
        String line = _client.readStringUntil('\n');
        line.trim();
        int sep = line.indexOf(':');
        if (sep < 0) continue;

        String key = line.substring(0, sep);
        String state = line.substring(sep + 1);
        key.trim();
        state.trim();
        _held[key] = (state == "1" || state == "PRESSED");
    }
}

bool KeyboardManagerClass::GetKey(const String& key) {
    return _held[key];
}

bool KeyboardManagerClass::GetKeyDown(const String& key) {
    return _held[key] && !_prev[key];
}

bool KeyboardManagerClass::GetKeyUp(const String& key) {
    return !_held[key] && _prev[key];
}
