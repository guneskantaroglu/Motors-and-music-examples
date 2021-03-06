#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>
int duty, fout;
int xA, xB, foutA, foutB;
int distA = xB - xA;
int distB = xA - xB;

int x, xold, xt, F; // input, position x, output, force F
int K = 10; // slope constant
byte count; //for print count-down


void setup() {

  MotorA.init();
  MotorB.init();
  analogReadAveraging(32);

}

void loop() {
  
  x = analogRead(A1); // initialize x  
  xA = analogRead(A1); // reading position of slider A
  
  xB = analogRead(A9); // reading position of slider B

//  foutA = 2*(xB-xA); // this will peak at x=1024/6
//  MotorA.torque(foutA);  // 1/4 or 1/2 ?
//
//  foutB = 2*(xA-xB); // this will peak at x=1024/6
//  MotorB.torque(foutB);  // 1/4 or 1/2 ?
  
 
  //xt = x % 250; //same force for each 250 range
  F = 0;
  if(x>10 && x<=512){
  F = -K *x/10.0;
  }
  if(x>512 && x<1010){
    F = K * x/50.0;
  }
  /*
  if (x > 100) F = - K * 20;
  if (x > 200) F = - K * 40;
  if (x > 300) F = - K * 80;
  if (x > 400) F = - K * 160;
  if (x > 500) F = - K * 320;
  if (x > 600) F = - K * 100;
  if (x > 700) F = - K * 0;
  if (x > 800) F = K * 100;
  if (x > 900) F = K * 200;
  if (x > 950) F = K * 250;
  */
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


