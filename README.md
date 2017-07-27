# esp8266-oled-weather
Weather forecast using ESP8266+OLED

### 1. Install PlatformIO library

* install OLED SSD1306 driver library
```shell
pio lib install 562
```

### 2. Wire OLED () with ESP8266 (NodeMCU board)

    NodeMCU <--> OLED 128x64 (SSD1306) SPI interface
    D5 <-> CLK (D0)
    D7 <-> MOSI (D1)
    D0 <-> RES
    D2 <-> DC
    D8 <-> CS


