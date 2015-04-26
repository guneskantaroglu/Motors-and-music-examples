#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

int xA, xB, F, AF, BF; // input, position x, output, force F
int K = 10; // slope constant

int c = 0;

void setup() {
  
  MotorA.init();
  MotorB.init();
  analogReadAveraging(32);
  
  Music.init();
  Music.setGain1(0);
  Music.setGain2(0);
  Music.setGain3(0);
  
  Music.setFrequency1(500);
  Music.setFrequency2(1000);
  
}

void loop() {
  
  xA =  analogRead(A1);
  xB = analogRead(A9);


  F = 0;
  if (xA > 10 && xA <= 512) {
    F = -K * xA / 10.0;
  }
  else if (xA > 512 && xA < 1010) {
    F = K * xA / 10.0;        
  }
  AF = F;
  MotorA.torque(F);

//Serial.println(F);

  F = 0;
  if (xB > 10 && xB <= 512) {
    F = -K * xB / 10.0;
  }
  else if (xB > 512 && xB < 1010) {
    F = K * xB / 10.0;
    //Serial.println (BF);    
  }
  
  BF = F;
  MotorB.torque(F);
  
  float GA = (float) abs(AF) / 1023.0;  
  Music.setGain1(GA);

  float GB = (float) abs(BF) / 1023.0;  
  Music.setGain2(GB);
  
  c++;
  if(c >= 300) {
    Serial.print(AF); Serial.print(" - "); Serial.println(BF);
    c = 0;
  }

}
