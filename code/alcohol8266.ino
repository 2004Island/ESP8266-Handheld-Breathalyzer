#include <TFT_eSPI.h>
#include <SPI.h>
#include "graphics.h"

#define TFT_BLUE 0x757F
#define TFT_YELLOWGREEN 0xC749

TFT_eSPI tft = TFT_eSPI();

const int alcPin = A0;
int sensorValue = 0;

void setup() {
  // TFT setup
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setRotation(3);

  // Loading Animation (MQ3 Sensor needs to warm up)
  for (int i = 0; i < 50; i++) {
    tft.fillRect(55, 67-i, 40, i, TFT_ORANGE);
    tft.drawBitmap(50, 10, epd_bitmap_allArray[6], 60, 60, TFT_WHITE);
    delay(6000);
    tft.fillRect(50, 10, 60, 60, TFT_BLACK);
  }
  
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("MQ3 Alcohol", 10, 10, 1);
  tft.drawString("Meter", 10, 20, 1);
  tft.setTextSize(2);
}

void loop() {
  // read the analog in value
  sensorValue = analogRead(alcPin);
 
  if (sensorValue < 170) {
    drawScreen(0, TFT_BLUE);

  } else if (sensorValue >= 170 && sensorValue < 340) {
    drawScreen(1, TFT_GREEN);

  } else if (sensorValue >= 340 && sensorValue < 510) {
    drawScreen(2, TFT_YELLOWGREEN);

  } else if (sensorValue >= 510 && sensorValue < 680) {
    drawScreen(3, TFT_YELLOW);

  } else if (sensorValue >= 680 && sensorValue < 850) {
    drawScreen(4, TFT_ORANGE);

  } else {
    drawScreen(5, TFT_RED);
  }

}

void drawScreen(int type, uint16_t color) {
  tft.drawBitmap(75, -10, epd_bitmap_allArray[type], 100, 100, color);
  tft.fillRectHGradient(11, 58, 60, 10, TFT_GREEN, TFT_RED);
  tft.drawRect(10, 57, 62, 12, TFT_WHITE);
  tft.fillRect(10 + (sensorValue/18), 55, 5, 16, TFT_WHITE);
  tft.drawCentreString(String(sensorValue), 40, 35, 1);
  delay(500);
  tft.fillRect(10, 34, 80, 20, TFT_BLACK);
  tft.fillRect(75, -10, 100, 100, TFT_BLACK);
  tft.fillRect(10, 55, 80, 20, TFT_BLACK);
}