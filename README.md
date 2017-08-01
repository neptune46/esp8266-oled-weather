# esp8266-oled-weather
Weather forecast using ESP8266+OLED

### 1. Install PlatformIO library

* install OLED SSD1306 driver library
```shell
pio lib install 562
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

[Install OpenCV-Python in Windows](http://opencv-python-tutroals.readthedocs.io/en/latest/py_tutorials/py_setup/py_setup_in_windows/py_setup_in_windows.html)

    Installing OpenCV from prebuilt binaries

    Below Python packages are to be downloaded and installed to their default locations.

    1.1. Python-2.7.x.
    1.2. Numpy.
    1.3. Matplotlib (Matplotlib is optional).

    Install all packages into their default locations. Python will be installed to C:/Python27/.

    After installation, open Python IDLE. Enter import numpy and make sure Numpy is working fine.
    
    Download latest OpenCV release from sourceforge site and double-click to extract it.
    
    Goto opencv/build/python/2.7 folder.
    
    Copy cv2.pyd to C:/Python27/lib/site-packeges.
    
    Open Python IDLE and type following codes in Python terminal.

    >>> import cv2
    >>> print cv2.__version__
    
    If the results are printed out without any errors, congratulations !!! You have installed OpenCV-Python successfully.

### 4. Pictures

* ![pic](https://github.com/neptune46/esp8266-oled-weather/blob/master/picture/esp-oled-weather.jpg)


