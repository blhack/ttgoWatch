// The basic menu code
// If you add an app, this is where you will update the
// framework code to include it in the menu.
//
// Make the following updates:
// 1) Update maxApp to the total number of apps.
// 2) Update appName to add the title of the app.
// 3) in the main routine in TWatch_framework, add a case to the switch statement to call your app routine.


const int maxApp = 7; // number of apps
String appName[maxApp] = {"Exit", "DemoApp", "DemoApp1", "TouchDemo", "GetRequest", "DrawBox", "Reset Steps"}; // app names

uint8_t modeMenu() {
  int mSelect = 0; // The currently highlighted app
  int16_t x, y, tx, ty;

  boolean exitMenu = false; // used to stay in the menu until user selects app

  setMenuDisplay(0); // display the list of Apps

  while (!exitMenu) {
    if (watch->getTouch(x, y)) { // If you have touched something...

      while (watch->getTouch(tx, ty)) {} // wait until you stop touching

      if (y >= 160) { // you want the menu list shifted up
        mSelect += 1;
        if (mSelect == maxApp) mSelect = 0;
        setMenuDisplay(mSelect);
      }

      if (y <= 80) { // you want the menu list shifted down
        mSelect -= 1;
        if (mSelect < 0) mSelect = maxApp - 1;
        setMenuDisplay(mSelect);
      }
      if (y > 80 && y < 160) { // You selected the middle
        exitMenu = true;
      }
    }
  }
  //Return with mSelect containing the desired mode
  watch->tft->fillScreen(TFT_BLACK);
  return mSelect;
}

void setMenuDisplay(int mSel) {
  watch->tft->setTextFont(1);
  int curSel = 0;
  // Display mode header
  watch->tft->fillScreen(TFT_BLUE);
  watch->tft->fillRect(0, 80, 239, 80, TFT_BLACK);

  // Display apps
  if (mSel == 0) curSel = maxApp - 1;
  else curSel = mSel - 1;

  watch->tft->setTextSize(2);
  watch->tft->setTextColor(TFT_GREEN);
  watch->tft->setCursor(50, 30);
  watch->tft->println(appName[curSel]);

  watch->tft->setTextSize(3);
  watch->tft->setTextColor(TFT_RED);
  watch->tft->setCursor(40, 110);
  watch->tft->println(appName[mSel]);

  if (mSel == maxApp - 1) curSel = 0;
  else curSel = mSel + 1;

  watch->tft->setTextSize(2);
  watch->tft->setTextColor(TFT_GREEN);
  watch->tft->setCursor(50, 190);
  watch->tft->print(appName[curSel]);
}
