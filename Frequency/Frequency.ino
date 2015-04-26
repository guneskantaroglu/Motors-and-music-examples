#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

int oldxA, oldxB, newxA, newxB, F, AF, BF, newDis, oldDis; // input, position x, output, force F
int K = 10; // slope constant

//sound variables
int xA =  analogRead(A1);
int xB = analogRead(A9);

int dis = (xA + xB);

float gain = 0.0f;
float decay = 0.999f;

int c = 0;

void setup() {

  Music.init();
  Music.getPreset(20);
  Music.disableEnvelope1();
  Music.disableEnvelope2();
  Music.setWaveform(SINE);
  Music.setGain(0.0f);
  Music.setFrequency(50);
  
  MotorA.init();
  MotorB.init();
  analogReadAveraging(32);
}

void loop() {

  int newxA = analogRead(A1);
  int newxB = analogRead(A9);
  int newDis = newxA + newxB;

  oldDis = xA + xB;

  int diff = abs(newDis - oldDis);
  if (newDis == oldDis || diff <= 6){
//    Music.setGain1(0.0f);
  } else if (newDis < oldDis && diff > 6) {
//    Music.setGain1(1.0f);
    gain = 1.0f;
    Music.setFrequency(50);
  } else if (newDis > oldDis && diff > 6) {
    gain = 1.0f;
//    Music.setGain1(1.0f);
    Music.setFrequency(250);
  } 
  gain = gain * decay;
  Music.setGain(gain);
  xA = newxA;
  xB = newxB;

/*
  F = 0;
  if (xA > 1 && xA <= 475) {
    F = K * xA / 10.0;
  }
  else if (xA > 550 && xA < 1010) {
    F = -K * ((xA / 10.0) / 2);
  }
  AF = F;
  MotorA.torque(F);

  F = 0;
  if (xB > 1 && xB <= 512) {
    F = K * xB / 10.0;
  }
  else if (xB > 512 && xB < 1010) {
    F = K * ((xB / 10.0) / 2);

  }
*/
  BF = F;
  MotorB.torque(F);
  
  Serial.println(newDis);
  Serial.println("/"); 
  Serial.println(xB);
  Serial.println("/");
  Serial.println(xA);
  
}
