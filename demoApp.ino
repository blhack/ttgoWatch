void demoApp() {

  watch->tft->fillScreen(TFT_BLACK);
  watch->tft->setCursor(0, 100);
  watch->tft->print("Demo app.  Touch the screen to exit back to main.: ");
  
  while (!watch->getTouch(x, y)) {} // Wait for touch
  while (watch->getTouch(x, y)) {
    watch->tft->fillScreen(TFT_BLACK);
    sleepTime = millis() + 5000;
    //clear the screen, and give another 5 seconds before sleeping again.
  }  
}
