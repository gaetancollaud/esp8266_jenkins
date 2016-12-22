#include "ws2812.h"


#define colorSaturation 20

WS2812::WS2812(NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>* strip) :  strip(strip){
}

void WS2812::init(){
  this->strip->Begin();
}

void WS2812::loop(unsigned long dtMs){
  this->accTime += dtMs;
  switch(this->animation){
    case FLASH:
      this->animateFlash();
      break;
    case CIRCLE:
      this->animateCircle();
      break;
  }
}

void WS2812::setColor(RgbColor color){
  this->animate(NONE, color, color);
}



void WS2812::animate(Animation animation, RgbColor back, RgbColor front){
  this->animation = animation;
  this->back = back;
  this->front = front;
  this->accTime = 0;
  if(animation==NONE){
    //apply none directly
    this->animateNone();
  }
}

void WS2812::animateNone(){
  this->strip->ClearTo(this->back);
  this->strip->Show();
}

void WS2812::animateFlash(){
  if(this->accTime>10000){
    this->strip->ClearTo(this->front);
  }else{
    unsigned long mod = this->accTime % 1000;
    if(mod<500){
      this->strip->ClearTo(this->back);
    }else{
      this->strip->ClearTo(this->front);
    }
  }
  this->strip->Show();
}

void WS2812::animateCircle(){
  int pixel = (this->accTime % 1200)/100;
  this->strip->ClearTo(this->back);
  this->strip->SetPixelColor(pixel, this->front);
  this->strip->Show();
}
