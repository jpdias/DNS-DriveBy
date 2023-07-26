#define GPSBaud 9600

#include "Log.h"
#include "Scan.h"
#include "Screen.h"

extern TinyGPSPlus tinyGPS;
extern SoftwareSerial ss;
extern SSD1306Wire display;

void setup()
{
  Serial.begin(115200);
  printHeader();

  display.init();
  display.flipScreenVertically();
  display.setFont(DejaVu_Sans_Mono_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.clear();
  drawSplash(2);
  // initialize GPS
  ss.begin(GPSBaud);
  bool gpsSuccess = initGPS();
  if (!gpsSuccess)
  {
    Serial.println("[-] RESTARTING");
    delay(500);
    ESP.reset();
  }
  delay(500);
  initWiFi();
}

void loop()
{
  dnsDriveby();
}