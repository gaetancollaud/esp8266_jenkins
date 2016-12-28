#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <FS.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>

#include <ws2812.h>
#include <OTA.h>
#include <jenkins.h>

#include "../config/config.h"

// SKETCH BEGIN
AsyncWebServer server(80);

const char * deviceName = "jenkins-status";

#define PIN_BUZZER 15
#define BUILTIN_LED 2
#define NB_PIXELS 12

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(NB_PIXELS, 2);

WS2812 ledStrip(&strip);
OTA ota(deviceName, BUILTIN_LED);
Jenkins jenkins(&server, &ledStrip, PIN_BUZZER);

void setup(){
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);
  digitalWrite(PIN_BUZZER, LOW);

  WiFi.begin(CONFIG_SSID, CONFIG_PASSWORD);

  MDNS.addService("http","tcp",80);

  static WiFiEventHandler e1, e2;
  e1 = WiFi.onStationModeGotIP([](WiFiEventStationModeGotIP ipInfo){
    Serial.printf("Got IP: %s\r\n", ipInfo.ip.toString().c_str());
    digitalWrite(BUILTIN_LED, LOW);
  });
	e2 = WiFi.onStationModeDisconnected([](WiFiEventStationModeDisconnected event_info){
    digitalWrite(BUILTIN_LED, HIGH);
  });


  server.begin();
  ledStrip.init();
  ota.init();
  jenkins.init();

  ledStrip.setColor(RgbColor(0,0,0));
}

unsigned long lastLoop = 0;
void loop(){
  unsigned long now = millis();
  unsigned long dtMs = 1;
  if (lastLoop < now) {
      //or else overflow, keep 1ms as arbitratry dtMs
      dtMs = now - lastLoop;
  }
  lastLoop = now;

  ArduinoOTA.handle();
  ota.loop();
  ledStrip.loop(dtMs);
  jenkins.loop(dtMs);
}
