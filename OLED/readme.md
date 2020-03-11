# oled

OLED with SSD1306 module (128x64 or 128x32) with I2C interface

## connection

Arduino Uno:

Display SDA pin   -> Arduino Analog 4 or the dedicated SDA pin  
Display SCL pin   -> Arduino Analog 5 or the dedicated SCL pin  

Arduino Mega:

Display SDA pin   -> Arduino Digital 20 (SDA) or the dedicated SDA pin  
Display SCL pin   -> Arduino Digital 21 (SCL) or the dedicated SCL pin  


## libraries

### Adafruit_SSD1306

https://github.com/adafruit/Adafruit_SSD1306

Use [I2C scanner](http://playground.arduino.cc/Main/I2cScanner) to detect device address, then use it to configure `display.begin` function

Modify `Adafruit_SSD1306.h` header file to specify device type. uncomment one of the following options:
```
//   #define SSD1306_128_64
//   #define SSD1306_128_32
//   #define SSD1306_96_16
```

### OLED_I2C

http://www.rinkydinkelectronics.com/library.php?id=80  
http://www.rinkydinkelectronics.com/library.php?id=82  
http://www.rinkydinkelectronics.com/library.php?id=84  

### U8g2

https://github.com/olikraus/u8g2

you need to uncomment appropriate constructor to configure library to work with you display, f.e.:
```
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display
```

## links

http://arduino-diy.com/arduino-oled-displey  
https://www.youtube.com/watch?v=niA3aPu3-dQ  
https://www.youtube.com/watch?v=oWazLlxFJ1Y  
https://www.youtube.com/watch?v=-IFwwWj11Kw  