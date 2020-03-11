
/*
 * Show messages on an 8x8 led matrix,
 * scrolling from right to left.
 *
 * Uses FrequencyTimer2 library to
 * constantly run an interrupt routine
 * at a specified frequency. This
 * refreshes the display without the
 * main loop having to do anything.
 *
 */

#include <FrequencyTimer2.h>

#define SPACE { \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}  \
}

#define A { \
  {0, 0, 0, 1, 1, 0, 0, 0}, \
  {0, 0, 1, 0, 0, 1, 0, 0}, \
  {0, 1, 0, 0, 0, 0, 1, 0}, \
  {0, 1, 0, 0, 0, 0, 1, 0}, \
  {0, 1, 1, 1, 1, 1, 1, 0}, \
  {0, 1, 0, 0, 0, 0, 1, 0}, \
  {0, 1, 0, 0, 0, 0, 1, 0}, \
  {0, 1, 0, 0, 0, 0, 1, 0}  \
}

#define B { \
  {1, 1, 1, 1, 0, 0, 0, 0}, \
  {1, 0, 0, 0, 1, 0, 0, 0}, \
  {1, 0, 0, 0, 1, 0, 0, 0}, \
  {1, 1, 1, 1, 0, 0, 0, 0}, \
  {1, 0, 0, 0, 1, 0, 0, 0}, \
  {1, 0, 0, 0, 1, 0, 0, 0}, \
  {1, 0, 0, 0, 1, 0, 0, 0}, \
  {1, 1, 1, 1, 0, 0, 0, 0}  \
}

#define C { \
  {0, 0, 1, 1, 1, 1, 0, 0}, \
  {0, 1, 1, 0, 0, 1, 1, 0}, \
  {0, 1, 0, 0, 0, 0, 1, 0}, \
  {0, 1, 0, 0, 0, 0, 0, 0}, \
  {0, 1, 0, 0, 0, 0, 0, 0}, \
  {0, 1, 0, 0, 0, 0, 1, 0}, \
  {0, 1, 1, 0, 0, 1, 1, 0}, \
  {0, 0, 1, 1, 1, 1, 0, 0}  \
}

#define D { \
    {1, 1, 1, 1, 1, 1, 0, 0}, \
    {0, 1, 1, 0, 0, 1, 0, 0}, \
    {0, 1, 1, 0, 0, 0, 1, 1}, \
    {0, 1, 1, 0, 0, 0, 1, 1}, \
    {0, 1, 1, 0, 0, 0, 1, 1}, \
    {0, 1, 1, 0, 0, 0, 1, 1}, \
    {0, 1, 1, 0, 0, 1, 0, 0}, \
    {1, 1, 1, 1, 1, 1, 0, 0}  \
}

#define H { \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 1, 1, 1, 1, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}  \
}

#define E  { \
    {0, 1, 1, 1, 1, 1, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 1, 1, 1, 1, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 1, 1, 1, 1, 1, 0}  \
}

#define L { \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 1, 1, 1, 1, 1, 0}  \
}

#define O { \
    {0, 0, 0, 1, 1, 0, 0, 0}, \
    {0, 0, 1, 0, 0, 1, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 0, 1, 0, 0, 1, 0, 0}, \
    {0, 0, 0, 1, 1, 0, 0, 0}  \
}

#define R { \
    {1, 1, 1, 1, 1, 1, 0, 0}, \
    {0, 1, 1, 0, 0, 1, 1, 0}, \
    {0, 1, 1, 0, 0, 1, 1, 0}, \
    {0, 1, 1, 1, 1, 1, 0, 0}, \
    {0, 1, 1, 0, 0, 1, 1, 0}, \
    {0, 1, 1, 0, 0, 1, 1, 0}, \
    {0, 1, 1, 0, 0, 0, 1, 1}, \
    {1, 1, 1, 0, 0, 0, 1, 1}  \
}

#define T { \
  {1, 1, 1, 1, 1, 1, 1, 1}, \
  {0, 0, 0, 1, 1, 0, 0, 0}, \
  {0, 0, 0, 1, 1, 0, 0, 0}, \
  {0, 0, 0, 1, 1, 0, 0, 0}, \
  {0, 0, 0, 1, 1, 0, 0, 0}, \
  {0, 0, 0, 1, 1, 0, 0, 0}, \
  {0, 0, 0, 1, 1, 0, 0, 0}, \
  {0, 0, 0, 1, 1, 0, 0, 0} \
}

#define Y { \
  {1, 1, 0, 0, 0, 0, 1, 1}, \
  {0, 1, 0, 0, 0, 0, 1, 0}, \
  {0, 0, 1, 0, 0, 1, 0, 0}, \
  {0, 0, 0, 1, 1, 0, 0, 0}, \
  {0, 0, 0, 1, 1, 0, 0, 0}, \
  {0, 0, 0, 1, 1, 0, 0, 0}, \
  {0, 0, 0, 1, 1, 0, 0, 0}, \
  {0, 0, 0, 1, 1, 0, 0, 0}  \
}
#define V { \
  {1, 1, 0, 0, 0, 0, 1, 1}, \
  {1, 1, 0, 0, 0, 0, 1, 1}, \
  {1, 1, 0, 0, 0, 0, 1, 1}, \
  {1, 1, 0, 0, 0, 0, 1, 1}, \
  {1, 1, 0, 0, 0, 0, 1, 1}, \
  {0, 0, 1, 0, 0, 1, 0, 0}, \
  {0, 0, 0, 1, 1, 0, 0, 0}, \
  {0, 0, 0, 1, 1, 0, 0, 0}  \
}

#define I { \
  {0, 0, 1, 1, 1, 1, 0, 0}, \
  {0, 0, 0, 1, 1, 0, 0, 0}, \
  {0, 0, 0, 1, 1, 0, 0, 0}, \
  {0, 0, 0, 1, 1, 0, 0, 0}, \
  {0, 0, 0, 1, 1, 0, 0, 0}, \
  {0, 0, 0, 1, 1, 0, 0, 0}, \
  {0, 0, 0, 1, 1, 0, 0, 0}, \
  {0, 0, 1, 1, 1, 1, 0, 0}  \
}

#define Z { \
    {1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 0, 0, 0, 0, 1, 1}, \
    {1, 0, 0, 0, 0, 1, 1, 0}, \
    {0, 0, 0, 0, 1, 1, 0, 0}, \
    {0, 0, 0, 1, 1, 0, 0, 0}, \
    {0, 0, 1, 1, 0, 0, 0, 1}, \
    {0, 1, 1, 0, 0, 0, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1}  \
}



byte col = 0;
byte leds[8][8];


// col[xx] of leds = pin yy on led matrix
const int cols[8] = {
  2, 7, 19, 5, 13, 18, 12, 16
};

// row[xx] of leds = pin yy on led matrix
const int rows[8] = {
  9, 8, 4, 17, 3, 10, 11, 6
};

const int numPatterns = 22;
byte patterns[numPatterns][8][8] = {
  SPACE,H,A,C,T,Y,A,SPACE,V,I,Z,D,O,R,A,V,L,I,V,A,I,SPACE
};

int pattern = 0;

void setup() {
  // sets the pins as output
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    // initialize the output pins:
    pinMode(cols[thisPin], OUTPUT);
    pinMode(rows[thisPin], OUTPUT);
  }

  // set up cols and rows
  for (int i = 1; i <= 8; i++) {
    digitalWrite(cols[i - 1], LOW);
  }

  for (int i = 1; i <= 8; i++) {
    digitalWrite(rows[i - 1], LOW);
  }

  clearLeds();

  // Turn off toggling of pin 11
  FrequencyTimer2::disable();
  // Set refresh rate (interrupt timeout period)
  FrequencyTimer2::setPeriod(2000);
  // Set interrupt routine to be called
  FrequencyTimer2::setOnOverflow(display);

  setPattern(pattern);
}

void loop() {
    pattern = ++pattern % numPatterns;
    slidePattern(pattern, 60);
}

void clearLeds() {
  // Clear display array
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      leds[i][j] = 0;
    }
  }
}

void setPattern(int pattern) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      leds[i][j] = patterns[pattern][i][j];
    }
  }
}

void slidePattern(int pattern, int del) {
  for (int l = 0; l < 8; l++) {
    for (int i = 0; i < 7; i++) {
      for (int j = 0; j < 8; j++) {
        leds[j][i] = leds[j][i+1];
      }
    }

    int textStartCollumn = 7;

    for (int j = 0; j < 8; j++) {
      leds[j][textStartCollumn] = patterns[pattern][j][0 + l];
    }
    delay(del);
  }
}

// Interrupt routine
void display() {
  digitalWrite(cols[col], LOW);  // Turn whole previous column off
  col++;
  if (col == 8) {
    col = 0;
  }
  for (int row = 0; row < 8; row++) {
    if (leds[col][7 - row] == 1) {
      digitalWrite(rows[row], LOW);  // Turn on this led
    }
    else {
      digitalWrite(rows[row], HIGH); // Turn off this led
    }
  }
  digitalWrite(cols[col], HIGH); // Turn whole column on at once (for equal lighting times)
}
