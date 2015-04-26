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
  Music.setWaveform1(NOISE);
  Music.setWaveform2(SAW);



}

void loop() {

  int posA = analogRead(A1);
  int posB = analogRead(A9);

  int freqA = map(posA, 0, 1023, 50, 500);
  int freqB = map(posB, 30, 645, 50, 500);

  Music.setFrequency1((float)freqA);
  Music.setFrequency2((float)freqB);

}
