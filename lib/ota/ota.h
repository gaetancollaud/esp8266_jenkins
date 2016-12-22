#ifndef _OTA_H
#define _OTA_H

#include <ArduinoOTA.h>
#include "Arduino.h"

#define DEBUG_TIMEMANAGER

#ifdef DEBUG_TIMEMANAGER
#define DEBUGTIMEMANAGER(...) Serial.printf(__VA_ARGS__)
#else
#define DEBUGTIMEMANAGER(...)
#endif

class OTA {
public:
  OTA(const char* deviceName, int statudLed);

	void init();

  void loop();

protected:
  const char* deviceName;
  int statusLed;
  bool wasOn;
};

#endif
