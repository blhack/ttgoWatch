void drawBox() {

  watch->tft->fillScreen(TFT_BLACK);
  watch->tft->setCursor(0, 0);

  watch->tft->fillRect(80, 20, 159, 80, TFT_WHITE);
  
  while (!watch->getTouch(x, y)) {} // Wait for touch
  while (watch->getTouch(x, y)) {
    watch->tft->fillScreen(TFT_BLACK);
    sleepTime = millis() + 5000;
    //give another 5 seconds before sleeping again.
  }  // Wait for release
}
