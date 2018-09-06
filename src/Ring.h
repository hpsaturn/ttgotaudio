#ifndef RING_H
#define RING_H

#include <Adafruit_NeoPixel.h>

class Ring {

public:
  Ring(void);
  Adafruit_NeoPixel strip;
  void
    colorWipe (uint32_t c, uint8_t wait),
    pulseWhite (uint8_t wait),
    rainbowFade2White(uint8_t wait, int rainbowLoops, int whiteLoops),
    whiteOverRainbow(uint8_t wait, uint8_t whiteSpeed, uint8_t whiteLength ),
    fullWhite(),
    rainbowCycle(uint8_t wait),
    rainbow(uint8_t wait);
  uint32_t
    Wheel(byte WheelPos),
    Color(uint8_t r, uint8_t g, uint8_t b);
  uint8_t
    red(uint32_t c),
    green(uint32_t c),
    blue(uint32_t c);

private:

};

#endif
