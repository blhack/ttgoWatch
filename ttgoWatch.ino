#include "config.h"
#include <time.h>
#include <soc/rtc.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "skylab";
const char* password = "***REMOVED***";

#define uS_TO_S_FACTOR 1000000

TTGOClass *watch;
TFT_eSPI *tft;
BMA *sensor;
bool irq = false;
uint32_t tiltCount = 0;
uint32_t clickCount = 0;
uint32_t stepCount = 0;
int per;
int sleepCountdown;
int hh;
int mm;
int ss;
RTC_Date tnow;
int16_t x, y;
int16_t xoffset = 30;
int sleepTime;
bool sleeping = false;

void timer_wakeup() {
  Serial.println("You woke up from a timer.  This will fire every 60 seconds to do things like alarms.");
  digitalWrite(4, HIGH);
  delay(300);
  digitalWrite(4, LOW);
  sleeping = true;
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_39, 1);
  esp_sleep_enable_timer_wakeup(uS_TO_S_FACTOR * 15 * 60);
  esp_light_sleep_start();
}

void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : timer_wakeup(); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}

void setup()
{
    Serial.begin(115200);
    pinMode(4, OUTPUT);
    print_wakeup_reason();
    // Get TTGOClass instance
    watch = TTGOClass::getWatch();

    // Initialize the hardware, the BMA423 sensor has been initialized internally
    watch->begin();
    watch->rtc->check();
    watch->rtc->syncToSystem();


    // Turn on the backlight
    watch->openBL();

    //Receive objects for easy writing
    tft = watch->tft;
    sensor = watch->bma;

    // Accel parameter structure
    Acfg cfg;
    /*!
        Output data rate in Hz, Optional parameters:
            - BMA4_OUTPUT_DATA_RATE_0_78HZ
            - BMA4_OUTPUT_DATA_RATE_1_56HZ
            - BMA4_OUTPUT_DATA_RATE_3_12HZ
            - BMA4_OUTPUT_DATA_RATE_6_25HZ
            - BMA4_OUTPUT_DATA_RATE_12_5HZ
            - BMA4_OUTPUT_DATA_RATE_25HZ
            - BMA4_OUTPUT_DATA_RATE_50HZ
            - BMA4_OUTPUT_DATA_RATE_100HZ
            - BMA4_OUTPUT_DATA_RATE_200HZ
            - BMA4_OUTPUT_DATA_RATE_400HZ
            - BMA4_OUTPUT_DATA_RATE_800HZ
            - BMA4_OUTPUT_DATA_RATE_1600HZ
    */
    cfg.odr = BMA4_OUTPUT_DATA_RATE_100HZ;
    /*!
        G-range, Optional parameters:
            - BMA4_ACCEL_RANGE_2G
            - BMA4_ACCEL_RANGE_4G
            - BMA4_ACCEL_RANGE_8G
            - BMA4_ACCEL_RANGE_16G
    */
    cfg.range = BMA4_ACCEL_RANGE_2G;
    /*!
        Bandwidth parameter, determines filter configuration, Optional parameters:
            - BMA4_ACCEL_OSR4_AVG1
            - BMA4_ACCEL_OSR2_AVG2
            - BMA4_ACCEL_NORMAL_AVG4
            - BMA4_ACCEL_CIC_AVG8
            - BMA4_ACCEL_RES_AVG16
            - BMA4_ACCEL_RES_AVG32
            - BMA4_ACCEL_RES_AVG64
            - BMA4_ACCEL_RES_AVG128
    */
    cfg.bandwidth = BMA4_ACCEL_NORMAL_AVG4;

    /*! Filter performance mode , Optional parameters:
        - BMA4_CIC_AVG_MODE
        - BMA4_CONTINUOUS_MODE
    */
    cfg.perf_mode = BMA4_CONTINUOUS_MODE;

    // Configure the BMA423 accelerometer
    sensor->accelConfig(cfg);

    // Enable BMA423 accelerometer
    // Warning : Need to use feature, you must first enable the accelerometer
    // Warning : Need to use feature, you must first enable the accelerometer
    // Warning : Need to use feature, you must first enable the accelerometer
    sensor->enableAccel();

    pinMode(BMA423_INT1, INPUT);
    attachInterrupt(BMA423_INT1, [] {
        // Set interrupt to set irq value to 1
        irq = 1;
    }, RISING); //It must be a rising edge

    // Enable BMA423 isStepCounter feature
    sensor->enableFeature(BMA423_STEP_CNTR, true);
    // Enable BMA423 isTilt feature
    sensor->enableFeature(BMA423_TILT, true);
    // Enable BMA423 isDoubleClick feature
    sensor->enableFeature(BMA423_WAKEUP, true);

    // Reset steps
    //sensor->resetStepCounter();

    // Turn on feature interrupt
    sensor->enableStepCountInterrupt(false);
    sensor->enableTiltInterrupt();
    // It corresponds to isDoubleClick interrupt
    sensor->enableWakeupInterrupt();

    tft->setTextFont(4);
    tft->setTextColor(TFT_WHITE, TFT_BLACK);

    // Some display settings
    esp_sleep_enable_timer_wakeup(uS_TO_S_FACTOR * 15 * 60);
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_39, 1);
    sleepTime = millis() + 5000;
}

void loop() {
  if (sleeping == true) {
    if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_TIMER) {
      timer_wakeup();
    } else {
      watch->displayWakeup();
      watch->openBL();
      sleeping = false;
      sleepTime = millis() + 5000;
      watch->rtc->syncToSystem();
      setCpuFrequencyMhz(160);
    }
  }
  tft->setTextColor(TFT_WHITE, TFT_BLACK);
    if (irq) {
        irq = 0;
        bool  rlst;
        do {
            // Read the BMA423 interrupt status,
            // need to wait for it to return to true before continuing
            rlst =  sensor->readInterrupt();
        } while (!rlst);
    }

    if (sensor->getCounter() != stepCount) {
      tft->setTextColor(TFT_BLACK);
    tft->setCursor(xoffset, 42);
    tft->print("StepCount:");
    tft->print(stepCount);
    }
    stepCount = sensor->getCounter();
    tft->setTextColor(TFT_RED);
    tft->setCursor(xoffset, 42);
    tft->print("StepCount:");
    tft->print(stepCount);

    if ((watch->power->getBattPercentage()) != per) {
      tft->setTextColor(TFT_BLACK);
      tft->setCursor(xoffset, 84);
      tft->print("Battery:");
      tft->print(per);
    }
    per = watch->power->getBattPercentage();
    tft->setTextColor(TFT_GREEN);
    tft->setCursor(xoffset, 84);
    tft->print("Battery:");
    tft->print(per);

    if (watch->rtc->getDateTime().minute != mm) {
      tft->setTextColor(TFT_BLACK);
      tft->setCursor(xoffset, 126);
      bool pm = false;
      if (hh > 12) {
        hh = hh - 12;
        pm = true;
      }
      tft->print(hh);
      tft->print(":");
      if (mm < 10) {
        tft->print("0");
      }
      tft->print(mm);
      if (pm == true) {
        tft->print(" PM");
      } else {
        tft->print(" AM");
      }
    }

    tnow = watch->rtc->getDateTime();
    hh = tnow.hour;
    mm = tnow.minute;
    ss = tnow.second;
    int dday = tnow.day;
    int mmonth = tnow.month;
    int yyear = tnow.year;

    tft->setTextColor(TFT_WHITE);
    tft->setCursor(xoffset, 126);
    bool pm = false;
    if (hh > 12) {
      hh = hh - 12;
      pm = true;
    }
    tft->print(hh);
    tft->print(":");
    if (mm < 10) {
      tft->print("0");
    }
    tft->print(mm);
    if (pm == true) {
      tft->print(" PM");
    } else {
      tft->print(" AM");
    }

    tft->setTextColor(TFT_RED);
    tft->setCursor(xoffset, 168);
    tft->print("Drink water.");

    if ((sleepTime - millis()) != sleepCountdown) {
      tft->setTextColor(TFT_BLACK);
      tft->setCursor(xoffset, 195);
      tft->print("Sleep in: ");
      tft->print(sleepCountdown);
    }
    sleepCountdown = sleepTime - millis();
    tft->setTextColor(TFT_WHITE);
    tft->setCursor(xoffset, 195);
    tft->print("Sleep in: ");
    tft->print(sleepCountdown);

    if (watch->getTouch(x, y)) {
      Serial.println("You touched me!");
      while (watch->getTouch(x, y)) {} // wait for user to release
      switch (modeMenu()) { // Call modeMenu. The return is the desired app number
        case 0: // Zero is the clock, just exit the switch
          sleepTime = millis() + 5000;
          break;
        case 1:
          demoApp();
          break;
        case 2:
          demoApp1();
          break;
        case 3:
          touchDemo();
          break;
        case 4:
          getRequest();
          break;
        case 5:
          drawBox();
          break;
        case 6:
          resetSteps();
          break;
        case 7:
          break;
        case 8:
          break;
        case 9:
          break;
        }
      }

  if (millis() > sleepTime) {
    setCpuFrequencyMhz(20);
    watch->closeBL();
    watch->displaySleep();
    sleeping = true;
    esp_light_sleep_start();
  }
  Serial.println(sensor->getCounter());
  delay(100);
}
