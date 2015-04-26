#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

int xA, xB, F, AF, BF; // input, position x, output, force F
int K = 5; // slope constant

void setup() {

  MotorA.init();
  MotorB.init();
  analogReadAveraging(32);


}

void loop() {

  xA = analogRead(A1);
  xB = analogRead(A9);


  F = 0;
  if (xA > 10 && xA <= 400) {
    F = - K * xA / 10.0;
  }
   if (xA > 400 && xA <= 450 ) {
    F = K * xA / 10.0;
  }
   if (xA > 450 && xA <= 600 ) {
    F = - K * xA / 10.0;
  }
    if (xA > 600 && xA <= 800 ) {
    F = K * xA / 10.0;
  }
  else if (xA > 800 && xA < 1010) {
    F = - K * xA / 10.0;
  }
  AF = F;
  MotorA.torque(F);

  //Serial.println(F);

  F = 0;
  if (xB > 10 && xB <= 400) {
    F = - K * xA / 10.0;
  }
   if (xB > 400 && xB <= 450 ) {
    F = K * xA / 10.0;
  }
   if (xB > 450 && xB <= 600 ) {
    F = - K * xA / 10.0;
  }
    if (xB > 600 && xB <= 800 ) {
    F = K * xA / 10.0;
  }
  else if (xB > 800 && xB < 1010) {
    F = - K * xB / 10.0;
  }

  BF = F;
  MotorB.torque(F);


}
