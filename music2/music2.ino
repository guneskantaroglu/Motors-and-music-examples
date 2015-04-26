#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>
byte waveFormArray[] = { SINE,
                        SQUARE,
                        PULSE,
                        TRIANGLE,
                        SAW,
                        FUZZ,
                        DIGI1,
                        DIGI2,
                        DIGI3,
                        DIGI4,
                        NOISE,
                        DIGI6,
                        TAN1,
                        TAN2,
                        TAN3,
                        TAN4
                       };


void setup() {
  Music.init();
  


}

void loop() {
  
  int posA = analogRead(A1);
  int posB = analogRead(A9);
  
  int freqA = map(posA, 0, 1023, 500, 1500);
  
  float ampB = (float) posB/645.0;
  
  int waveform = map(posB, 30, 645, 0, 5);
  //waveform = constrain(waveform, 0,6);
  Music.setWaveform(waveFormArray[waveform]);
  
  Music.setWaveform(SAW);
  
  
  Music.setFrequency1(freqA);
  //Music.setGain(ampB);
 
}
