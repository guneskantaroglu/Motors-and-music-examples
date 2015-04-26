#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

int p = 0;
int posA = 0;
int posB = 0;
int posAmax = 0;
int posAmin = 0;
int posBmax = 0;
int posBmin = 0;


void setup() {
  MotorA.init();
  MotorB.init();

  while (millis() < 10000) {
    posA = analogRead(A1);
    posB = analogRead(A9);

    if (posA > posAmax) {
      posAmax = posA;
    }

    if (posA < posAmin) {
      posAmin = posA;
    }

    if (posB > posBmax) {
      posBmax = posB;
    }

    if (posB < posBmin) {
      posBmin = posB;
    }
  }

}

void loop() {
  p++;

  posA = analogRead(A1);
  posB = analogRead(A9);

  posA = map(posA, posAmin, posAmax, 0, 1023);
  posB = map(posB, posBmin, posBmax, 0, 1023);

  posA = constrain(posA, 0, 1023);
  posB = constrain(posB, 0, 1023);

  int torqueA = (posB - posA);
  int torqueB = (posA - posB);

  if (p % 200 == 0) {
    Serial.print("Pos: "); Serial.println(posA);
    Serial.print("- Tor: "); Serial.println(torqueA);
  }

  MotorA.torque(torqueA);
  MotorB.torque(torqueB);


}
