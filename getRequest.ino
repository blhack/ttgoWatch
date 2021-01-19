void getRequest() {

  watch->tft->fillScreen(TFT_BLACK);
  watch->tft->setCursor(0, 10);
  watch->tft->print("Touch the screen to do a get request.");

  while (!watch->getTouch(x, y)) {} // Wait for touch
  while (watch->getTouch(x, y)) {}
  watch->tft->fillScreen(TFT_BLACK);
  watch->tft->setCursor(0, 10);
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
    HTTPClient http;

    http.begin("http://zombo.com/"); //Specify the URL
    int httpCode = http.GET();                                        //Make the request

    if (httpCode > 0) { //Check for the returning code

        String payload = http.getString();
        watch->tft->print("\n");
        watch->tft->print(httpCode);
      }
    http.end(); //Free the resources
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
  watch->tft->print("\ntap the screen to exit.");
  
  while (!watch->getTouch(x, y)) {} // Wait for touch
  while (watch->getTouch(x, y)) {
    watch->tft->fillScreen(TFT_BLACK);
    sleepTime = millis() + 5000;
    //give another 5 seconds before sleeping again.
  }  // Wait for release
  
}
