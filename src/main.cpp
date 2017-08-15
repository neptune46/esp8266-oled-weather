#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
#include <SPI.h> // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Spi.h"
#include "SH1106SPi.h"
#include "icon.h"
#include "character.h"
#include "number.h"
#include "symbol.h"

// Initialize the OLED display using SPI
// D5 -> CLK
// D7 -> MOSI (DOUT)
// D0 -> RES
// D2 -> DC
// D8 -> CS
SSD1306Spi        display(D0, D2, D8);

#define DEMO_DURATION 1000
typedef void (*Demo)(int);

int demoMode = 0;
int counter = 1;

void connectHttps();

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println();

  connectHttps();

  // Initialising the UI will init the display too.
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

}

void drawFontFaceDemo(int i) {
    // Font Demo1
    // create more fonts at http://oleddisplay.squix.ch/
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "Hello world");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 10, "Hello world");
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 26, "Hello world");
}

void drawRectDemo(int i) {
      // Draw a pixel at given position
    for (int i = 0; i < 10; i++) {
      display.setPixel(i, i);
      display.setPixel(10 - i, i);
    }
    display.drawRect(12, 12, 20, 20);

    // Fill the rectangle
    display.fillRect(14, 14, 17, 17);

    // Draw a line horizontally
    display.drawHorizontalLine(0, 40, 20);

    // Draw a line horizontally
    display.drawVerticalLine(40, 0, 20);
}

void drawImageDemo(int i) {

    display.drawXbm(0, 0, ICON_WIDTH, ICON_HEIGHT, icon_list[i]);

    display.drawVerticalLine(60, 0, 64);

    display.drawXbm(64, 0, CHARACTER_WIDTH, CHARACTER_HEIGHT, character_list[i]);

    display.drawHorizontalLine(60, 32, 68);

    display.drawXbm(64+0*8, 32, NUMBER_WIDTH, NUMBER_HEIGHT, number_list[2]);
    display.drawXbm(64+1*8, 32, NUMBER_WIDTH, NUMBER_HEIGHT, number_list[5]);
    display.drawXbm(64+2*8, 32, SYMBOL_WIDTH, SYMBOL_HEIGHT, symbol_list[0]); // ~
    display.drawXbm(64+4*8, 32, NUMBER_WIDTH, NUMBER_HEIGHT, number_list[3]);
    display.drawXbm(64+5*8, 32, NUMBER_WIDTH, NUMBER_HEIGHT, number_list[2]);
    display.drawXbm(64+6*8, 32, SYMBOL_WIDTH, SYMBOL_HEIGHT, symbol_list[1]); // C

    display.drawXbm(64+0*8, 48, NUMBER_WIDTH, NUMBER_HEIGHT, number_list[0]);
    display.drawXbm(64+1*8, 48, NUMBER_WIDTH, NUMBER_HEIGHT, number_list[8]);
    display.drawXbm(64+2*8, 48, SYMBOL_WIDTH, SYMBOL_HEIGHT, symbol_list[2]); // month
    display.drawXbm(64+4*8, 48, NUMBER_WIDTH, NUMBER_HEIGHT, number_list[1]);
    display.drawXbm(64+5*8, 48, NUMBER_WIDTH, NUMBER_HEIGHT, number_list[0]);
    display.drawXbm(64+6*8, 48, SYMBOL_WIDTH, SYMBOL_HEIGHT, symbol_list[3]); // day

    display.drawRect(0, 0, 128, 64);
}


Demo demos[] = { drawFontFaceDemo, drawRectDemo, drawImageDemo };
int demoLength = (sizeof(demos) / sizeof(Demo));

int array_index = 0;

void loop() {
  // clear the display
  display.clear();

  // draw the current demo method
  //demos[demoMode](array_index);

  drawImageDemo(array_index);
  //array_num = 5;
  array_index = (array_index + 1) % icon_num;

  // write the buffer to the display
  display.display();

  counter++;
  delay(1000);
}