# IR distance sensor - GP2Y0A21YK0F

This SHARP distance sensor bounces IR off objects to determine how far away they are. It returns an analog voltage that can be used to determine how close the nearest object is. Comes with 12" long 3-JST interface wire. These sensors are good for short-range detection. For over 1 m distance, we suggest using sonar sensors

To use, connect black wire to ground, red wire to 5V and white wire to analog input. The analog voltage out will range from 3V when an object is only 4" (10 cm) away and 0.4V when the object is 32" (80 cm) away

[datasheet](./datasheet/gp2y0a21yk_e.pdf)

## src/ir-distance-sensor

sample that show raw data and measurement from `SharpIR` library


## links

http://electromicro.ru/market/datchiki_i_sensory/infrakrasnyj_datchik_gp2y0a21yk0f/  
https://github.com/guillaume-rico/SharpIR  
