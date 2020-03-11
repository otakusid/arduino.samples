/*
 * Multiplexing can be used to display arbitrary patterns with led matrices. Multiplexing is sometimes also called scanning. It scans rows (usually from up to down) and lights needed leds only in one row at time. Something like following:
 *
 *  Start by having everything disconnected.
 *  Connect positive voltage all the needed columns.
 *  Connect row to ground. This lights the needed leds in the row.
 *  Disconnect the row and all columns.
 *  Do the same steps one by one to all rows and then start from the beginning.
 *
 * Do this slowly and you would see blinking LED rows. Do it really fast and human eye can see the whole pattern. Phenomenon is called persistence of vision.
*/

// 2-dimensional array of row pin numbers:
const int row_pins[8] = {
  2, 7, 19, 5, 13, 18, 12, 16
};

// 2-dimensional array of column pin numbers:
const int column_pins[8] = {
  6, 11, 10, 3, 17, 4, 8, 9
};


void setup() {
  /* Turn all columns off by setting then low. */
    for (uint8_t x=0; x<8; x++) {
        pinMode(column_pins[x], OUTPUT);
        digitalWrite(column_pins[x], HIGH);
    }

    /* Turn all rows off by setting then high. */
    for (uint8_t y=0; y<8; y++) {
        pinMode(row_pins[y], OUTPUT);
        digitalWrite(row_pins[y], LOW);
    }
}

uint8_t pattern[8][8]  = {
  {0,1,1,1,1,1,1,0},
  {1,0,1,1,1,1,0,1},
  {1,1,0,1,1,0,1,1},
  {1,1,1,0,0,1,1,1},
  {1,1,1,0,0,1,1,1},
  {1,1,0,1,1,0,1,1},
  {1,0,1,1,1,1,0,1},
  {0,1,1,1,1,1,1,0}
};

void draw(uint8_t pattern[8][8], uint8_t delayTime) {

    for (uint8_t row=0; row<8; ++row) {
        /* Connect or disconnect columns as needed. */
        for (uint8_t column=0; column<8; ++column) {
            digitalWrite(column_pins[column], pattern[row][column]);
        }

        /* Turn on whole row. */
        digitalWrite(row_pins[row], HIGH);

        delay(delayTime);

        /* Turn off whole row. */
        digitalWrite(row_pins[row], LOW);
    }
}

void loop() {
  /* With 100ms delay eye can see updating row by row. */
    for (uint8_t i=0; i<10; i++) {
        draw(pattern, 100);
    }

    /* With 10ms delay pattern appears but flickers. */
    for (uint16_t i=0; i<100; i++) {
        draw(pattern, 10);
    }

    /* Withoud delay solid pattern appears. */
    while (1) {
        draw(pattern, 1);
    }

}
