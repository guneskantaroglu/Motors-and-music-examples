#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>


void setup() {
  MotorA.init();
  MotorB.init();
  
}

void loop() {
  MotorB.torque(300);
  delay(1000);
  MotorB.torque(0);
  delay(2000);
  MotorB.torque(-300);
  delay(1000);

}
