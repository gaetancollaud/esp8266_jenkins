#ifndef _JENKINS_H
#define _JENKINS_H

#include <ESPAsyncWebServer.h>
#include <NeoPixelBus.h>
#include <ws2812.h>
#include <beep.h>

 #define MAX_LUMINOSITY 50

#define DEBUG_JENKINS

#ifdef DEBUG_JENKINS
#define DEBUG_JENKINS(...) Serial.printf(__VA_ARGS__)
#else
#define DEBUG_JENKINS(...)
#endif

class Jenkins {
public:
  Jenkins(AsyncWebServer* server, WS2812* ledStrip, Beep* beep);

	void init();

  void loop(unsigned long now);

protected:
  AsyncWebServer* server;
  WS2812* ledStrip;
  Beep* beep;
};

#endif
