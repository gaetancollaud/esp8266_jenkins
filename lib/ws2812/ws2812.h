#ifndef _WS2812_H
#define _WS2812_H

#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>
#include "Arduino.h"

enum Animation{
  NONE,
  FLASH,
  CIRCLE
};

class WS2812 {
public:
  WS2812(NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>* strip);

  void init();

  void loop(unsigned long now);

  void setColor(RgbColor color);

  void animate(Animation animation, RgbColor back, RgbColor front);

protected:

  unsigned long accTime;

  Animation animation;
  RgbColor back;
  RgbColor front;

  NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>* strip;

  void animateFlash();
  void animateCircle();
  void animateNone();
};

#endif
