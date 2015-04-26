#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>
int p = 0;

void setup() {
  MotorA.init();


}

void loop() {
  p++;

  int posA = analogRead(A1);

  int torqueA = (512 - posA);

  if (p % 200 == 0) {
    Serial.print("Pos: "); Serial.println(posA);
    Serial.print("torque: "); Serial.println(torqueA);
  }

  MotorA.torque(torqueA * 4);

}
