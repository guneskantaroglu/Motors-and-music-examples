#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>
int duty, fout;
int xA, xB, foutA, foutB;
int distA = xB - xA;
int distB = xA - xB;

int x, xold, xt, F; // input, position x, output, force F
int K = 30; // slope constant
byte count; //for print count-down


void setup() {

  MotorA.init();
  MotorB.init();
  analogReadAveraging(32);

}

void loop() {
  
    
  xA = analogRead(A1); // reading position of slider A
  
  xB = analogRead(A9); // reading position of slider B

  foutA = 2*(xB-xA); // this will peak at x=1024/6
  MotorA.torque(foutA);  // 1/4 or 1/2 ?

  foutB = 2*(xA-xB); // this will peak at x=1024/6
  MotorB.torque(foutB);  // 1/4 or 1/2 ?
  
 
  xt = x % 250; //same force for each 250 range
  F = 0;
  if (xt > 60) F = - K * (xt - 60);
  if (xt > 80) F = - K * (100 - xt);
  if (xt > 120) F =  K * (140 - xt);
  if (xt > 140) F = 0;
  MotorA.torque(F);
  
 
 // print every 256 cycles
  if(count++==0){
    Serial.print(x);
    Serial.print(" ");
    Serial.print(xt);
    Serial.print(" ");
    Serial.println(F);
  }

}


