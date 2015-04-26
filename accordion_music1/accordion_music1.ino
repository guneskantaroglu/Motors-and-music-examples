#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>
int duty, fout;
int xA, xB, foutA, foutB, x2 fa, fb;
int distA = xB - xA;
int distB = xA - xB;


int x, xAold, xBold, xt, F; // input, position x, output, force F
int K = 10; // slope constant
//int Kb = 10; // slope constant
byte count; //for print count-down


void setup() {
 Music.init();
  Music.setFrequency1(200);
  Music.setFrequency2(250);
  Music.setFrequency3(300); 
  
  MotorA.init();
  MotorB.init();
  analogReadAveraging(32);
  
  Serial.begin(9600);
  x = analogRead(A1); // initialize x
  xA = analogRead(A1); // reading position of slider A
  x2 = analogRead(A9); // initialize x2
  xB = analogRead(A9); // reading position of slider B

}

void loop() {
  
  xAold = x;
  x =  analogRead(A1);
  xBold = x2;
  x2 = analogRead(A9);
  
  if (F <= 10) {
  Music.setGain1(0.0f);
  Music.setFrequency1(200);
}
if (F <= 100) {
  Music.setGain2(0.0f);
  Music.setFrequency2(250);
}
if (F <= 200) {
  Music.setGain3(0.0f);
  Music.setFrequency3(300);
}
if (F <= 512) {
  Music.setGain1(1.0f);
  Music.setFrequency1(400);
  }
  else{
    Music.setGain1(0.9995f*Music.getGain1());
    Music.setGain2(0.9995f*Music.getGain2());
    Music.setGain3(0.9995f*Music.getGain3());
  }
  
//    if (((xBold <= 125) && (x2 > 125)) || ((xBold >= 125) && (x2 < 125))){
//  Music.setGain1(1.0f);
//  Music.setFrequency1(200);
//}
//if (((xBold <= 375) && (x2 > 375)) || ((xBold >= 375) && (x2 < 375))){
//  Music.setGain2(1.0f);
//  Music.setFrequency2(250);
//}
//if (((xBold <= 625) && (x2 > 625)) || ((xBold >= 625) && (x2 < 625))){
//  Music.setGain3(1.0f);
//  Music.setFrequency3(300);
//}
//if (((xBold <= 875) && (x2 > 875)) || ((xBold >= 875) && (x2 < 875))){
//  Music.setGain1(1.0f);
//  Music.setFrequency1(400);
//  }
//  else{
//    Music.setGain1(0.9995f*Music.getGain1());
//    Music.setGain2(0.9995f*Music.getGain2());
//    Music.setGain3(0.9995f*Music.getGain3());
//  }
  
  //force terrain

  F = 0;
  if (x > 10 && x <= 512) {
    F = -K * x / 10.0;
  }
  else if (x > 512 && x < 1010) {
    F = K * x / 10.0;
    Fa = F;
    MotorA.torque(Fa);
  }

Serial.println(F);

  F = 0;
  if (x2 > 10 && x2 <= 512) {
    F = -K * x2 / 10.0;
  }
  else if (x2 > 512 && x2 < 1010) {
    F = K * x2 / 10.0;
    Fb = F;
    MotorB.torque(Fb);
  }
//  F = 0;
//  if (x > 100) F = - K * 2;
//  if (x > 200) F = - K * 4;
//  if (x > 300) F = - K * 8;
//  if (x > 400) F = - K * 16;
//  if (x > 500) F = - K * 32;
//  if (x > 600) F = - K * 40;
//  if (x > 700) F = - K * 0;
//  if (x > 800) F = K * 51;
//  if (x > 900) F = K * 40;
//  if (x > 950) F = K * 36;
//  MotorA.torque(F);
//  
//  F = 0;
//  if (x2 > 100) F = - K * 2;
//  if (x2 > 200) F = - K * 4;
//  if (x2 > 300) F = - K * 8;
//  if (x2 > 400) F = - K * 16;
//  if (x2 > 500) F = - K * 32;
//  if (x2 > 600) F = - K * 40;
//  if (x2 > 700) F = - K * 0;
//  if (x2 > 800) F = K * 51;
//  if (x2 > 900) F = K * 40;
//  if (x2 > 950) F = K * 36;
//  MotorB.torque(F);
//  


}
//
//    // print every 256 cycles
//    if (count++ == 0) {
//      Serial.print(x);
//      Serial.print(" ");
//      Serial.print(xt);
//      Serial.print(" ");
//      Serial.println(F);
//    }




