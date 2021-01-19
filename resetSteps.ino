void resetSteps() {

  watch->tft->fillScreen(TFT_BLACK);
  watch->tft->setCursor(0,0);
  watch->tft->print("Reset your steps?");
  watch->tft->setCursor(20, 120);
  watch->tft->print("Yes");
  watch->tft->setCursor(200, 120);
  watch->tft->print("No");
  
  while (!watch->getTouch(x, y)) {} // Wait for touch
  while (watch->getTouch(x, y)) {
    if (x < 120) {
      sensor->resetStepCounter();
    }
    watch->tft->fillScreen(TFT_BLACK);
    sleepTime = millis() + 5000;
    //give another 5 seconds before sleeping again.
  }
}
