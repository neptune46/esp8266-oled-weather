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

typedef struct _WeatherData {
  int code;
  int min;
  int max;
  int month;
  int day;
} WeatherData;

#define DAY_NUM 3

WeatherData wthData[DAY_NUM];

void connectHttps(char **day1, char **day2, char **day3);

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println();

  char day1[5][32] = {};
  char day2[5][32] = {};
  char day3[5][32] = {};

  connectHttps((char**)day1, (char**)day2, (char**)day3);

  wthData[0].code = atoi(day1[0]);
  wthData[0].min = atoi(day1[1]);
  wthData[0].max = atoi(day1[2]);
  wthData[0].month = atoi(day1[3]);
  wthData[0].day = atoi(day1[4]);

  wthData[1].code = atoi(day2[0]);
  wthData[1].min = atoi(day2[1]);
  wthData[1].max = atoi(day2[2]);
  wthData[1].month = atoi(day2[3]);
  wthData[1].day = atoi(day2[4]);

  wthData[2].code = atoi(day3[0]);
  wthData[2].min = atoi(day3[1]);
  wthData[2].max = atoi(day3[2]);
  wthData[2].month = atoi(day3[3]);
  wthData[2].day = atoi(day3[4]);

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

    char code = wthData[i].code;
    char min = wthData[i].min;
    char max = wthData[i].max;
    char month = wthData[i].month;
    char day = wthData[i].day;

    display.drawXbm(0, 0, ICON_WIDTH, ICON_HEIGHT, icon_list[code]);

    display.drawVerticalLine(60, 0, 64);

    display.drawXbm(64, 0, CHARACTER_WIDTH, CHARACTER_HEIGHT, character_list[code]);

    display.drawHorizontalLine(60, 32, 68);

    display.drawXbm(64+0*8, 32, NUMBER_WIDTH, NUMBER_HEIGHT, number_list[min/10]);
    display.drawXbm(64+1*8, 32, NUMBER_WIDTH, NUMBER_HEIGHT, number_list[min%10]);
    display.drawXbm(64+2*8, 32, SYMBOL_WIDTH, SYMBOL_HEIGHT, symbol_list[0]); // ~
    display.drawXbm(64+4*8, 32, NUMBER_WIDTH, NUMBER_HEIGHT, number_list[max/10]);
    display.drawXbm(64+5*8, 32, NUMBER_WIDTH, NUMBER_HEIGHT, number_list[max%10]);
    display.drawXbm(64+6*8, 32, SYMBOL_WIDTH, SYMBOL_HEIGHT, symbol_list[1]); // C

    display.drawXbm(64+0*8, 48, NUMBER_WIDTH, NUMBER_HEIGHT, number_list[month/10]);
    display.drawXbm(64+1*8, 48, NUMBER_WIDTH, NUMBER_HEIGHT, number_list[month%10]);
    display.drawXbm(64+2*8, 48, SYMBOL_WIDTH, SYMBOL_HEIGHT, symbol_list[2]); // month
    display.drawXbm(64+4*8, 48, NUMBER_WIDTH, NUMBER_HEIGHT, number_list[day/10]);
    display.drawXbm(64+5*8, 48, NUMBER_WIDTH, NUMBER_HEIGHT, number_list[day%10]);
    display.drawXbm(64+6*8, 48, SYMBOL_WIDTH, SYMBOL_HEIGHT, symbol_list[3]); // day

    display.drawRect(0, 0, 128, 64);
}


Demo demos[] = { drawFontFaceDemo, drawRectDemo, drawImageDemo };
int demoLength = (sizeof(demos) / sizeof(Demo));

int day_index = 0;

void loop() {
  // clear the display
  display.clear();

  drawImageDemo(day_index);
  day_index = (day_index + 1) % DAY_NUM;

  // write the buffer to the display
  display.display();

  counter++;
  delay(1000);
}