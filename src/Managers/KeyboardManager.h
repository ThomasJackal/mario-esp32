#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <map>

class KeyboardManagerClass {
public:
    void begin(const char* ssid, const char* password, IPAddress host, uint16_t port);
    void update();

    bool GetKey(const String& key);
    bool GetKeyDown(const String& key);
    bool GetKeyUp(const String& key);

private:
    WiFiClient _client;
    IPAddress _host;
    uint16_t _port = 0;

    std::map<String, bool> _held;
    std::map<String, bool> _prev;
};

extern KeyboardManagerClass KeyboardManager;
