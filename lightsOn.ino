
void lightsOn() {
  const char ALL_RED[] = "{\"method\": \"setPilot\", \"params\": {\"dimming\": 100, \"state\": true, \"w\": 255}}";
  char packetBuffer[255];
  const unsigned int LIGHT_PORT = 38899;
  WiFiUDP Udp;
  //broadcastIp ip(10,69,0,255);


  watch->tft->fillScreen(TFT_BLACK);
  watch->tft->setCursor(0, 10);
  watch->tft->print("Standing down red alert.");
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
     hueLightsOn();
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
