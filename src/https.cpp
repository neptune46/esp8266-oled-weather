#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#include "define.h"

const char* ssid = "LINK025";
const char* password = "summerview@2013";

const char* host = "free-api.heweather.com";
const int httpsPort = 443;

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char* fingerprint = "40 e1 ec a0 b9 e1 68 6a aa 8c b9 51 a0 bd 3b 86 b5 03 aa 14";

void copyString(char* dst, const char* src, int length) {
  for(int i=0; i<length; i++) {
    dst[i] = src[i];
  }
}

void printWeather(WeatherString* day) {
  Serial.println(day->strCode);
  Serial.println(day->strMin);
  Serial.println(day->strMax);
  Serial.println(day->strMonth);
  Serial.println(day->strDay);
}

void copyWeather(WeatherString* day, const char* str[4]) {
  copyString(day->strCode, str[0], strlen(str[0]));
  copyString(day->strMin, str[1], strlen(str[1]));
  copyString(day->strMax, str[2], strlen(str[2]));
  day->strMonth[0] = str[3][5];
  day->strMonth[1] = str[3][6];
  day->strDay[0] = str[3][8];
  day->strDay[1] = str[3][9];

  printWeather(day);
}

void connectHttps(WeatherString* day1, WeatherString* day2, WeatherString* day3) {
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  if (client.verify(fingerprint, host)) {
    Serial.println("certificate matches");
  } else {
    Serial.println("certificate doesn't match");
  }

  String url = "/v5/forecast?city=shanghai&lang=en&key=0ea65b86e2a94335a1bbdb09017eb470";
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }

  DynamicJsonBuffer  jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(line);
  if (!root.success()) {
    Serial.println("parseObject() failed");
  } else {
    Serial.println("parseObject() success...");

    const char* str1[4];
    str1[0] = root["HeWeather5"][0]["daily_forecast"][0]["cond"]["code_d"];
    str1[1] = root["HeWeather5"][0]["daily_forecast"][0]["tmp"]["min"];
    str1[2] = root["HeWeather5"][0]["daily_forecast"][0]["tmp"]["max"];
    str1[3] = root["HeWeather5"][0]["daily_forecast"][0]["date"];
    copyWeather(day1, str1);
    
    const char* str2[4];
    str2[0] = root["HeWeather5"][0]["daily_forecast"][1]["cond"]["code_d"];
    str2[1] = root["HeWeather5"][0]["daily_forecast"][1]["tmp"]["min"];
    str2[2] = root["HeWeather5"][0]["daily_forecast"][1]["tmp"]["max"];
    str2[3] = root["HeWeather5"][0]["daily_forecast"][1]["date"];
    copyWeather(day2, str2);

    const char* str3[4];
    str3[0] = root["HeWeather5"][0]["daily_forecast"][2]["cond"]["code_d"];
    str3[1] = root["HeWeather5"][0]["daily_forecast"][2]["tmp"]["min"];
    str3[2] = root["HeWeather5"][0]["daily_forecast"][2]["tmp"]["max"];
    str3[3] = root["HeWeather5"][0]["daily_forecast"][2]["date"];
    copyWeather(day3, str3);
  }
}