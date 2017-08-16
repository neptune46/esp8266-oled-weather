#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#include <ArduinoJson.h>

const char* ssid = "LINK025";
const char* password = "summerview@2013";

const char* host = "free-api.heweather.com";
const int httpsPort = 443;

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char* fingerprint = "40 e1 ec a0 b9 e1 68 6a aa 8c b9 51 a0 bd 3b 86 b5 03 aa 14";

void connectHttps() {
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

    const char* day1[3];
    day1[0] = root["HeWeather5"][0]["daily_forecast"][0]["cond"]["code_d"];
    day1[1] = root["HeWeather5"][0]["daily_forecast"][0]["tmp"]["min"];
    day1[2] = root["HeWeather5"][0]["daily_forecast"][0]["tmp"]["max"];

    const char* day2[3];
    day2[0] = root["HeWeather5"][0]["daily_forecast"][1]["cond"]["code_d"];;
    day2[1] = root["HeWeather5"][0]["daily_forecast"][1]["tmp"]["min"];
    day2[2] = root["HeWeather5"][0]["daily_forecast"][1]["tmp"]["max"];

    const char* day3[3];
    day3[0] = root["HeWeather5"][0]["daily_forecast"][2]["cond"]["code_d"];
    day3[1] = root["HeWeather5"][0]["daily_forecast"][2]["tmp"]["min"];
    day3[2] = root["HeWeather5"][0]["daily_forecast"][2]["tmp"]["max"];

    Serial.println(day1[0]);
    Serial.println(day1[1]);
    Serial.println(day1[2]);

    Serial.println(day2[0]);
    Serial.println(day2[1]);
    Serial.println(day2[2]);

    Serial.println(day3[0]);
    Serial.println(day3[1]);
    Serial.println(day3[2]);
  }

  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");
}