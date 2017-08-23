#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
#include <SPI.h> // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Spi.h"
#include "SH1106SPi.h"
#include "icon.h"
#include "character.h"
#include "number.h"
#include "symbol.h"
#include "weather.h"

// Initialize the OLED display using SPI
// D5 -> CLK
// D7 -> MOSI (DOUT)
// D0 -> RES
// D2 -> DC
// D8 -> CS

SSD1306Spi display(D0, D2, D8);

int counter = 1;
int day_index = 0;

Weather wth;

void setup() 
{
  Serial.begin(9600);
  Serial.println();
  Serial.println();

  counter = 0;
  wth.queryWeather();

  // Initialising the UI will init the display too.
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

}

void drawImage(int i) 
{
    char code = wth.getWeatherCode(i);
    char min = wth.getTemperatureMin(i);
    char max = wth.getTemperatureMax(i);
    char month = wth.getMonth(i);
    char day = wth.getDay(i);

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

void loop() 
{
  // clear the display
  display.clear();

  drawImage(day_index);
  day_index = (day_index + 1) % DAY_NUM;

  // write the buffer to the display
  display.display();

  counter++;

  if(counter >= 2000) 
  {
    // update weather data per 100 minutes
    counter = 0;
    wth.queryWeather();
  }

  delay(DISPLAY_DURATION);
}