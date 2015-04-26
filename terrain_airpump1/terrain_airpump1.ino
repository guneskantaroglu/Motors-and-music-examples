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
  if (xA > 0 && xA <= 1010) {
    F = - K * xA / 10.0;
  }
  else if (xA < 1010) {
    F =  K * xA / 10.0;
  }
  AF = F;
  MotorA.torque(F);

  F = 0;
  if (xB > 0 && xB <= 1010) {
    F = - K * xB / 10.0;
  }
  else if (xB < 1010) {
    F =  K * xB / 10.0;
  }
  BF = F;
  MotorB.torque(F);

}
