// CenterAB - both motors
// xA->Freqequency1, xB->Frequency2
//CenterA at xB, CenterB at xA
//feels like "Slave"

#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

int duty, count, fout;
int xA, xB, foutA, foutB;

void setup(){
  MotorA.init();
  MotorB.init();  
  analogReadAveraging(32);
}

void loop(){
   
  xA = analogRead(A1);
  
  xB = analogRead(A9);

  
  foutA = 2*(xB-xA); // this will peak at x=1024/6
  MotorA.torque(foutA);  // 1/4 or 1/2 ?

  foutB = 2*(xA-xB); // this will peak at x=1024/6
  MotorB.torque(foutB);  // 1/4 or 1/2 ?


}
