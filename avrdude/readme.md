# AVRDUDE

AVRDUDE is a utility to download/upload/manipulate the ROM and EEPROM contents of AVR microcontrollers using the in-system programming technique (ISP)

## arduino

upload to **arduino uno** connected by usb:
```
avrdude -v -patmega328p -carduino -PCOM5 -b115200 -D -Uflash:w:C:\blink.ino.hex:i
```

command options description:

**-v** - enable verbose output  
**-p** - what type of part (MCU) that is connected to the programmer  
**-c** - programmer to be used  
**-P** - port to which the programmer is attached  
**-b** - baudrate  
**-D** - disable auto erase for flash  
**-U** - `-U memtype:op:filename[:format]`:  
*flash* - the flash ROM of the device  
*w* - read the specified file and write it to the specified device memory  
*C:\blink.ino.hex* - path to file with firmware  
*i* - Intel Hex


## links

[website](http://savannah.nongnu.org/projects/avrdude/)  
[documentation](http://www.nongnu.org/avrdude/user-manual/avrdude.html)
