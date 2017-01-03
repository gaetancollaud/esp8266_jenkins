#ifndef _BEEP_H
#define _BEEP_H

#include <morse.h>

 #define MAX_LUMINOSITY 50

class Beep {
public:
  Beep(int pinBuzzer);

	void init();

  void loop(unsigned long now);

  void play(String morseCode);

protected:
  int pinBuzzer;
  LEDMorseSender morse;
};

#endif
