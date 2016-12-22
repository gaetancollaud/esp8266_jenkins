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

#include "../config/config.h"

// SKETCH BEGIN
AsyncWebServer server(80);

const char * deviceName = "jenkins-status";

#define BUILTIN_LED 2
#define NB_PIXELS 12

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(NB_PIXELS, 2);

WS2812 ledStrip(&strip);
OTA ota(deviceName, BUILTIN_LED);

void setup(){
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  WiFi.begin(CONFIG_SSID, CONFIG_PASSWORD);

  MDNS.addService("http","tcp",80);

  server.on("/heap", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(ESP.getFreeHeap()));
  });
  server.on("/success", HTTP_GET, [&ledStrip](AsyncWebServerRequest *request){
    ledStrip.setColor(RgbColor(0, 100, 0));
    request->send(200, "text/plain", "ok");
  });
  server.on("/error", HTTP_GET, [&ledStrip](AsyncWebServerRequest *request){
    ledStrip.animate(FLASH, RgbColor(10, 0, 0), RgbColor(100, 0, 0));
    request->send(200, "text/plain", "ok");
  });
  server.on("/process", HTTP_GET, [&ledStrip](AsyncWebServerRequest *request){
    ledStrip.animate(CIRCLE, RgbColor(10, 5, 0), RgbColor(100, 50, 0));
    request->send(200, "text/plain", "ok");
  });
  server.on("/off", HTTP_GET, [&ledStrip](AsyncWebServerRequest *request){
    ledStrip.setColor(RgbColor(0, 0, 0));
    request->send(200, "text/plain", "ok");
  });

  server.begin();
  ledStrip.init();
  ota.init();
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
}
