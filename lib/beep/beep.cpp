#include "beep.h"

Beep::Beep(int pinBuzzer) : pinBuzzer(pinBuzzer), morse(LEDMorseSender(pinBuzzer, 24.0)){

}

void Beep::init(){
  morse.setup();
}


void Beep::loop(unsigned long now){
  	morse.continueSending();
}


void Beep::play(String morseCode){
  	morse.setMessage(morseCode);
    morse.startSending();
}
