
void redAlert() {
  const char ALL_RED[] = "{\"method\": \"setPilot\", \"params\": {\"dimming\": 100, \"state\": true, \"r\": 255, \"g\": 0, \"b\": 0}}";
  char packetBuffer[255];
  const unsigned int LIGHT_PORT = 38899;
  WiFiUDP Udp;

  watch->tft->fillScreen(TFT_BLACK);
  watch->tft->setCursor(0, 10);
  watch->tft->print("All stations\n, RED ALERT\n");
  watch->tft->print("Connecting to wifi..");
  WiFi.begin(ssid, password);
  uint32_t wifiStart = millis();
  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - wifiStart > 5000) {
      watch->tft->print("\nConnection failed tap to exit.");
      break;
    }
  }
  if (WiFi.status() == WL_CONNECTED) {
    watch->tft->print("Wifi Connected");
    watch->tft->print("\nSending request");
     Udp.beginPacket(BROADCASTIP, LIGHT_PORT);
     Udp.print(ALL_RED);
     Udp.endPacket();
     porchLightOn();
     hueRedAlert();
  }
  bool WiFi_Off();
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
  uint32_t wifiEndStart = millis();
  while (WiFi.status() == WL_CONNECTED) {
    if (millis() - wifiEndStart > 5000) {
      break;
    }
  }
  
  watch->tft->fillScreen(TFT_BLACK);
  sleepTime = millis() + 5000;

}
