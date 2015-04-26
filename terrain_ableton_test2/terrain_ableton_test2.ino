#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

///////motor variables
int xA, xB, F, AF, BF; // input, position x, output, force F
int K = 10; // slope constant

int end_cnt = 0;
int change = 0;
boolean meet = false;

/////sound variables
int oldxA, oldxB, newxA, newxB, newDis, oldDis; // input, position x, output, force F
int dis = (xA + xB);

int c = 0;

void setup() {

  MotorA.init();
  MotorB.init();
  analogReadAveraging(32);

  Music.init();

}


void loop() {
  
  int posA = analogRead(A1);
  int posB = analogRead(A9);

  while ((posA > 1000 && posA <= 1023) && (posB > 1000 && posB <= 1023)) {
    meet = true;

    posA = analogRead(A1);
    posB = analogRead(A9);

  }

  if (meet) {
    end_cnt++;
    if (end_cnt % 3 == 0) {
      change++;
    }
    meet = false;
    Serial.println(change);
    delay(200);
  }

//  if (change % 3 == 0)
    t0();
//  else if (change % 3 == 1)
//    t1();
//  else t2();


}

///////////////////////////////Terrains////////////////////////////////////

////////////////////////////Gradual Climb Up//////////////////////////////
void t0() {
  
  xA = analogRead(A1);
  xB = analogRead(A9);

  F = 0;
  if (xA > 0 && xA <= 1010) {
    F = - K * xA / 10.0;
  }
  else if (xA < 1010) {
    F =  K * xA / 10.0;
  }
  AF = F;
  freqT0A(); 
  MotorA.torque(F);
 

  F = 0;
  if (xB > 0 && xB <= 1010) {
    F = - K * xB / 10.0;
  }
  else if (xB < 1010) {
    F =  K * xB / 10.0;
  }
  BF = F;
  freqT0B();
  MotorB.torque(F);

  Serial.println("0");
}

////////////////////////////End Terrain//////////////////////////////

///////////////////////////////Sound////////////////////////////////
///////////////////////Gradual Climb Up ////////////////////////////

void freqT0A(){
  int newxA = analogRead(A1);
  int newxB = analogRead(A9);
  int newDis = newxA + newxB;
  int c = 0;

  oldDis = xA + xB;

  int diff = abs(newDis - oldDis);
  if (newDis == oldDis || diff <= 6){
  } else if (newDis < oldDis && diff > 6) {

    usbMIDI.sendNoteOn(62, 127, 1);
    c++;
    if(c >= 500) { 
    usbMIDI.sendNoteOff(62, 0, 1);
    c=0;
    }
    delay(100);
  }
    
    
   else if (newDis > oldDis && diff > 6) {
    
    usbMIDI.sendNoteOn(64, 127, 2);
    c++;
    if(c >= 500) { 
    usbMIDI.sendNoteOff(64, 0, 2);
    c=0;
    }
    delay(100);
  } 

  xA = newxA;
  xB = newxB; 
}

void freqT0B(){
  int newxA = analogRead(A1);
  int newxB = analogRead(A9);
  int newDis = newxA + newxB;
  int c=0;

  oldDis = xA + xB;

  int diff = abs(newDis - oldDis);
  if (newDis == oldDis || diff <= 6){
  } else if (newDis < oldDis && diff > 6) {

    usbMIDI.sendNoteOn(50, 127, 3);
    c++;
    if(c >= 500) { 
    usbMIDI.sendNoteOff(50, 0, 3);
    c=0;
    }
    delay(100);
    
  } else if (newDis > oldDis && diff > 6) {
    usbMIDI.sendNoteOn(75, 127, 4);
    c++;
    if(c >= 500) { 
    usbMIDI.sendNoteOff(75, 0, 4);
    c=0;
    }
    delay(100);
  } 
  
  xA = newxA;
  xB = newxB; 
}
