# esp8266-oled-weather
Weather forecast using ESP8266+OLED

### 1. Install PlatformIO library

Install OLED SSD1306 driver library
```shell
pio lib install 562
```
Install ArduinoJson library
```shell
pio lib install 64
```

### 2. Wire OLED with ESP8266 (NodeMCU board)

    NodeMCU <--> OLED 128x64 (SSD1306) SPI interface
    D5 <-> CLK (D0)
    D7 <-> MOSI (D1)
    D0 <-> RES
    D2 <-> DC
    D8 <-> CS

### 3. Convert image file as OLED displayable array

Use Img2Array.py to convert weather icon image to binary image array for OLED display
To run Img2Array.py, need install below python libraries 

    pip install -i https://pypi.tuna.tsinghua.edu.cn/simple numpy
    pip install -i https://pypi.tuna.tsinghua.edu.cn/simple opencv-python
    pip install -i https://pypi.tuna.tsinghua.edu.cn/simple matplotlib

### 4. Pictures

* ![pic1](https://github.com/neptune46/esp8266-oled-weather/blob/master/picture/pic1.jpg)



