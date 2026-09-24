#include <WiFi.h>

const char* ssid = "honor-7x";
const char* password = "ab403679356f$¿A";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(WiFi.status());
  }
  Serial.print("WiFi connected with IP:");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client;
   if(!client.connect(IPAddress(192,168,43,174), 10000)){
    Serial.println("Connection to host failed");
    delay(1000);
    return;
  }
  Serial.println("client connected sending packet");
  client.print("Hello from ESP32!");
  client.stop();
  delay(1000);
}