void demoApp2() {

  watch->tft->fillScreen(TFT_BLACK);
  watch->tft->setCursor(0, 100);
  watch->tft->print("Demo app 2.  Touch the screen to exit back to main.: ");
  
  while (!watch->getTouch(x, y)) {} // Wait for touch
  while (watch->getTouch(x, y)) {
    watch->tft->fillScreen(TFT_BLACK);
    sleepTime = millis() + 5000;
    //give another 5 seconds before sleeping again.
  }  // Wait for release
}
