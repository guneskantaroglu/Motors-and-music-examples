#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>
int p = 0;

void setup() {
  MotorA.init();
  MotorB.init();

}

void loop() {
  p++;

  int posA = analogRead(A1);
  int posB = analogRead(A9);
  
  int torqueA = (posB - posA);
  int torqueB = (posA - posB);


  if (p % 200 == 0) {
    Serial.print("Pos: "); Serial.println(posA);
    Serial.print("- Tor: "); Serial.println(torqueA);
  }

  MotorA.torque(torqueA);
  MotorB.torque(torqueB);


}
