
#include "weather.h"

void connectHttps(WeatherString* day1, WeatherString* day2, WeatherString* day3);

Weather::Weather() 
{

}

Weather::~Weather() 
{

}

int Weather::code2Index(int code) 
{
    int index = 0;
    switch (code) 
    {
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
  
void Weather::convertWeather(WeatherString* day, WeatherData* data) 
{
  data->code  = code2Index(atoi(day->strCode));
  data->min   = atoi(day->strMin);
  data->max   = atoi(day->strMax);
  data->month = atoi(day->strMonth);
  data->day   = atoi(day->strDay);
}

void Weather::queryWeather()
{
    WeatherString day1 = {};
    WeatherString day2 = {};
    WeatherString day3 = {};

    connectHttps(&day1, &day2, &day3);

    convertWeather(&day1, &wthData[0]);
    convertWeather(&day2, &wthData[1]);
    convertWeather(&day3, &wthData[2]);
}
