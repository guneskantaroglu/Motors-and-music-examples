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
  Serial.begin(9600);
  MotorA.init();
  MotorB.init();
  Music.init();
  Music.setWaveform1(0);//8bit default?
  Music.setWaveform2(0);
  Music.setGain1(1.0f);
  Music.setGain2(1.0f);
  
  analogReadAveraging(32);
}

void loop(){
   
  xA = analogRead(A1);
  Music.setFrequency1(map (xA, 0, 1023, 40, 2000)); 
  
  xB = analogRead(A9);
  Music.setFrequency2(map (xB, 0, 1023, 40, 2000)); 
  
  foutA = -6*(xA-xB); // this will peak at x=1024/6
  MotorA.torque(foutA);  // 1/4 or 1/2 ?

  foutB = -6*(xB-xA); // this will peak at x=1024/6
  MotorB.torque(foutB);  // 1/4 or 1/2 ?

  Music.setGain(float(abs(xA-xB))/1024.0f);

}
