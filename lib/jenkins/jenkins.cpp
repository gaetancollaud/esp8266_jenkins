#include "jenkins.h"

Jenkins::Jenkins(AsyncWebServer* server, WS2812* ledStrip, int pinBuzzer) : server(server), ledStrip(ledStrip), pinBuzzer(pinBuzzer){

}

void Jenkins::init(){
  server->on("/success", HTTP_GET, [this](AsyncWebServerRequest *request){
    ledStrip->setColor(RgbColor(0, MAX_LUMINOSITY, 0));
    request->send(200, "text/plain", "ok");
  });
  server->on("/error", HTTP_GET, [this](AsyncWebServerRequest *request){
    ledStrip->animate(FLASH, RgbColor(10, 0, 0), RgbColor(MAX_LUMINOSITY, 0, 0));
    request->send(200, "text/plain", "ok");
  });
  server->on("/process", HTTP_GET, [this](AsyncWebServerRequest *request){
    ledStrip->animate(CIRCLE, RgbColor(10, 5, 0), RgbColor(MAX_LUMINOSITY, MAX_LUMINOSITY>>1, 0));
    request->send(200, "text/plain", "ok");
  });
  server->on("/beep", HTTP_GET, [this](AsyncWebServerRequest *request){
    digitalWrite(pinBuzzer, HIGH);
    request->send(200, "text/plain", "ok");
  });
  server->on("/off", HTTP_GET, [this](AsyncWebServerRequest *request){
    ledStrip->setColor(RgbColor(0, 0, 0));
    digitalWrite(pinBuzzer, LOW);
    request->send(200, "text/plain", "ok");
  });
}


void Jenkins::loop(unsigned long now){

}
