#include "ota.h"

OTA::OTA(const char* deviceName, int statusLed):deviceName(deviceName), statusLed(statusLed), wasOn(false){
}

void OTA::init(){

  pinMode(statusLed, OUTPUT);

  ArduinoOTA.setHostname(deviceName);
  // ArduinoOTA.setPassword("admin");

  ArduinoOTA.onStart([&]() {
    DEBUGTIMEMANAGER("OTA Start updating \n");
  });
  ArduinoOTA.onEnd([&]() {
    DEBUGTIMEMANAGER("OTA End");
    digitalWrite(statusLed, HIGH);
  });
  ArduinoOTA.onProgress([&](unsigned int progress, unsigned int total) {
    DEBUGTIMEMANAGER("Progress: %u%%\n", (progress / (total / 100)));
    wasOn = !wasOn;
    digitalWrite(statusLed, wasOn ? LOW : HIGH);
  });
  ArduinoOTA.onError([&](ota_error_t error) {
    DEBUGTIMEMANAGER("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  DEBUGTIMEMANAGER("Ready for OTA\n");
}

void OTA::loop(){
  ArduinoOTA.handle();
}
