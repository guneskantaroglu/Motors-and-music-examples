#define MIDI_CHANNEL 1

#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

long time;
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  time = millis();
  if (time % 100 == 0) {
    usbMIDI.sendControlChange(07, 127, 1);
    Serial.println("send");

  }
  
    if (time % 300 == 0) {
    usbMIDI.sendControlChange(07, 1, 1);
    Serial.println("send");

  }

}
