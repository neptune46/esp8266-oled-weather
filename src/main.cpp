#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
#include <SPI.h> // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Spi.h"
#include "SH1106SPi.h"
#include "icon.h"
#include "character.h"
#include "number.h"
#include "symbol.h"
#include "define.h"
// Initialize the OLED display using SPI
// D5 -> CLK
// D7 -> MOSI (DOUT)
// D0 -> RES
// D2 -> DC
// D8 -> CS
SSD1306Spi        display(D0, D2, D8);

#define DEMO_DURATION 3000
typedef void (*Demo)(int);

int demoMode = 0;
int counter = 1;

WeatherData wthData[DAY_NUM];

int code2Index(int code) {
  int index = 0;
  switch (code) {
    case 100: index = 0; break;
    case 101: index = 1; break;
    case 102: index = 2; break;
    case 103: index = 3; break;
    case 104: index = 4; break;
    case 200: index = 5; break;
    case 201: index = 6; break;
    case 202: index = 7; break;
    case 203: index = 8; break;
    case 204: index = 9; break;
    case 205: index = 10; break;
    case 206: index = 11; break;
    case 207: index = 12; break;
    case 208: index = 13; break;
    case 209: index = 14; break;
    case 210: index = 15; break;
    case 211: index = 16; break;
    case 212: index = 17; break;
    case 213: index = 18; break;
    case 300: index = 19; break;
    case 301: index = 20; break;
    case 302: index = 21; break;
    case 303: index = 22; break;
    case 304: index = 23; break;
    case 305: index = 24; break;
    case 306: index = 25; break;
    case 307: index = 26; break;
    case 308: index = 27; break;
    case 309: index = 28; break;
    case 310: index = 29; break;
    case 311: index = 30; break;
    case 312: index = 31; break;
    case 313: index = 32; break;
    case 400: index = 33; break;
    case 401: index = 34; break;
    case 402: index = 35; break;
    case 403: index = 36; break;
    case 404: index = 37; break;
    case 405: index = 38; break;
    case 406: index = 39; break;
    case 407: index = 40; break;
    case 500: index = 41; break;
    case 501: index = 42; break;
    case 502: index = 43; break;
    case 503: index = 44; break;
    case 504: index = 45; break;
    case 507: index = 46; break;
    case 508: index = 47; break;
    case 900: index = 48; break;
    case 901: index = 49; break;
    case 999: index = 50; break;
    default: index = 50; break;
  }
  return index;
}

void convertWeather(WeatherString* day, WeatherData* data) {
  data->code  = code2Index(atoi(day->strCode));
  data->min   = atoi(day->strMin);
  data->max   = atoi(day->strMax);
  data->month = atoi(day->strMonth);
  data->day   = atoi(day->strDay);
}

void connectHttps(WeatherString* day1, WeatherString* day2, WeatherString* day3);

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println();

  WeatherString day1 = {};
  WeatherString day2 = {};
  WeatherString day3 = {};

  connectHttps(&day1, &day2, &day3);

  convertWeather(&day1, &wthData[0]);
  convertWeather(&day2, &wthData[1]);
  convertWeather(&day3, &wthData[2]);

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
  delay(DEMO_DURATION);
}