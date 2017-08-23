
#include <stdio.h>
#include <stdlib.h>

#include "define.h"

class Weather 
{
public:
    Weather();
    ~Weather();
    void queryWeather();
    char getWeatherCode(int i) { return wthData[i].code; };
    char getTemperatureMin (int i) { return wthData[i].min; };
    char getTemperatureMax (int i) { return wthData[i].max; };
    char getMonth (int i) { return wthData[i].month; };
    char getDay (int i) { return wthData[i].day; };
private:
    int code2Index(int code);
    void convertWeather(WeatherString* day, WeatherData* data);
    WeatherData wthData[DAY_NUM];
};