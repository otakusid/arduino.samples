# 4-channel I2C-safe Bi-directional Logic Level Converter

after wiring you should connect all not used outputs to GND because by default it outputs height level

## how it work

```
5V -> hv4 = lv4 -> 3.3V
5V <- hv3 = lv3 <- 3.3V
GND -> hv2 = lv2 -> GND
GND <- hv1 = lv1 <- GND
```

### links

https://learn.sparkfun.com/tutorials/bi-directional-logic-level-converter-hookup-guide
