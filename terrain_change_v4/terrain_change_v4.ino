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

float gain = 0.0f;
float decay = 0.999f;

int c = 0;

void setup() {

  MotorA.init();
  MotorB.init();
  analogReadAveraging(32);

  Music.init();
  Music.setGain1(0);
  Music.setGain2(0);
  Music.setGain3(0);
  
  Music.getPreset(20);
  Music.disableEnvelope1();
  Music.disableEnvelope2();
  Music.setWaveform(SINE);
  Music.setGain(0.0f);
  Music.setFrequency(50);


}


void loop() {
  
  int posA = analogRead(A1);
  int posB = analogRead(A9);

  //    Serial.print(posA);
  //    Serial.print(" ");
  //    Serial.println(posB);
  //
  while ((posA > 1000 && posA <= 1023) && (posB > 1000 && posB <= 1023)) {
    meet = true;
    //Serial.println("aaa");
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

  //Serial.println(end_cnt);

  if (change % 3 == 0)
    t0();
  else if (change % 3 == 1)
    t1();
  else t2();


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

////////////////////////////Curvy Slope//////////////////////////////

void t2() {
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
  freqT2A(); 
  MotorA.torque(F);

  F = 0;
  if (xB > 10 && xB <= 512) {
    F = -K * xB / 10.0;
  }
  else if (xB > 512 && xB < 1010) {
    F = K * xB / 10.0;
  }

  BF = F;
  freqT2B(); 
  MotorB.torque(F);
  Serial.println("2");
}


////////////////////////////Valley//////////////////////////////

void t3() {
  F = 0;
  if (xA > 1 && xA <= 475) {
    F = K * xA / 10.0;
  }
  else if (xA > 550 && xA < 1010) {
    F = -K * ((xA / 10.0) / 2);
  }
  AF = F;
  freqT3A(); 
  MotorA.torque(F);


  F = 0;
  if (xB > 1 && xB <= 475) {
    F = K * xB / 10.0;
  }
  else if (xB > 550 && xB < 1010) {
    F = K * ((xB / 10.0) / 2);
  }

  BF = F;
  freqT3B(); 
  MotorB.torque(F);

}

////////////////////////////Bumpy Road//////////////////////////////
void t1() {
  xA = analogRead(A1);
  xB = analogRead(A9);


  F = 0;
  if (xA > 10 && xA <= 400) {
    F = - K * xA / 10.0;
  }
  if (xA > 400 && xA <= 450 ) {
    F = K * xA / 10.0;
  }
  if (xA > 450 && xA <= 600 ) {
    F = - K * xA / 10.0;
  }
  if (xA > 600 && xA <= 800 ) {
    F = K * xA / 10.0;
  }
  else if (xA > 800 && xA < 1010) {
    F = - K * xA / 10.0;
  }
  AF = F;
  freqT1A(); 
  MotorA.torque(F);

  //Serial.println(F);

  F = 0;
  if (xB > 10 && xB <= 400) {
    F = - K * xA / 10.0;
  }
  if (xB > 400 && xB <= 450 ) {
    F = K * xA / 10.0;
  }
  if (xB > 450 && xB <= 600 ) {
    F = - K * xA / 10.0;
  }
  if (xB > 600 && xB <= 800 ) {
    F = K * xA / 10.0;
  }
  else if (xB > 800 && xB < 1010) {
    F = - K * xB / 10.0;
  }

  BF = F;
  freqT1B(); 
  MotorB.torque(F);
  Serial.println("1");
}

////////////////////////////End Terrain//////////////////////////////

///////////////////////////////Sound////////////////////////////////
///////////////////////Gradual Climb Up ////////////////////////////

void freqT0A(){
  int newxA = analogRead(A1);
  int newxB = analogRead(A9);
  int newDis = newxA + newxB;

  oldDis = xA + xB;

  int diff = abs(newDis - oldDis);
  if (newDis == oldDis || diff <= 6){
//    Music.setGain1(0.0f);
  } else if (newDis < oldDis && diff > 6) {
//    Music.setGain1(1.0f);
    gain = 1.0f;
    usbMIDI.sendNoteOn(62, 127, 1);
  } else if (newDis > oldDis && diff > 6) {
    gain = 1.0f;
//    Music.setGain1(1.0f);
    usbMIDI.sendNoteOn(64, 127, 2);
  } 
  gain = gain * decay;
  Music.setGain(gain);
  xA = newxA;
  xB = newxB; 
}

void freqT0B(){
  int newxA = analogRead(A1);
  int newxB = analogRead(A9);
  int newDis = newxA + newxB;

  oldDis = xA + xB;

  int diff = abs(newDis - oldDis);
  if (newDis == oldDis || diff <= 6){
//    Music.setGain1(0.0f);
  } else if (newDis < oldDis && diff > 6) {
//    Music.setGain1(1.0f);
    gain = 1.0f;
    usbMIDI.sendNoteOn(66, 127, 3);
  } else if (newDis > oldDis && diff > 6) {
    gain = 1.0f;
//    Music.setGain1(1.0f);
    usbMIDI.sendNoteOn(68, 127, 4);
  } 
  gain = gain * decay;
  Music.setGain(gain);
  xA = newxA;
  xB = newxB; 
}

//////////////////////////////T1 //////////////////////////////

void freqT1A(){
  int newxA = analogRead(A1);
  int newxB = analogRead(A9);
  int newDis = newxA + newxB;

  oldDis = xA + xB;

  int diff = abs(newDis - oldDis);
  if (newDis == oldDis || diff <= 6){
//    Music.setGain1(0.0f);
  } else if (newDis < oldDis && diff > 6) {
//    Music.setGain1(1.0f);
    gain = 1.0f;
    usbMIDI.sendNoteOn(62, 127, 1);
  } else if (newDis > oldDis && diff > 6) {
    gain = 1.0f;
//    Music.setGain1(1.0f);
    usbMIDI.sendNoteOn(64, 127, 1);
  } 
  gain = gain * decay;
  Music.setGain(gain);
  xA = newxA;
  xB = newxB; 
}

void freqT1B(){
  int newxA = analogRead(A1);
  int newxB = analogRead(A9);
  int newDis = newxA + newxB;

  oldDis = xA + xB;

  int diff = abs(newDis - oldDis);
  if (newDis == oldDis || diff <= 6){
//    Music.setGain1(0.0f);
  } else if (newDis < oldDis && diff > 6) {
//    Music.setGain1(1.0f);
    gain = 1.0f;
    usbMIDI.sendNoteOn(62, 127, 1);
  } else if (newDis > oldDis && diff > 6) {
    gain = 1.0f;
//    Music.setGain1(1.0f);
    usbMIDI.sendNoteOn(64, 127, 1);
  } 
  gain = gain * decay;
  Music.setGain(gain);
  xA = newxA;
  xB = newxB; 
}

///////////////////////////T2 //////////////////////////////////////////

void freqT2A(){
  int newxA = analogRead(A1);
  int newxB = analogRead(A9);
  int newDis = newxA + newxB;

  oldDis = xA + xB;

  int diff = abs(newDis - oldDis);
  if (newDis == oldDis || diff <= 6){
//    Music.setGain1(0.0f);
  } else if (newDis < oldDis && diff > 6) {
//    Music.setGain1(1.0f);
    gain = 1.0f;
    usbMIDI.sendNoteOn(62, 127, 1);
  } else if (newDis > oldDis && diff > 6) {
    gain = 1.0f;
//    Music.setGain1(1.0f);
    usbMIDI.sendNoteOn(64, 127, 1);
  } 
  gain = gain * decay;
  Music.setGain(gain);
  xA = newxA;
  xB = newxB; 
}

void freqT2B(){
  int newxA = analogRead(A1);
  int newxB = analogRead(A9);
  int newDis = newxA + newxB;
  

  oldDis = xA + xB;

  int diff = abs(newDis - oldDis);
  if (newDis == oldDis || diff <= 6){
//    Music.setGain1(0.0f);
  } else if (newDis < oldDis && diff > 6) {
//    Music.setGain1(1.0f);
    gain = 1.0f;
    usbMIDI.sendNoteOn(62, 127, 1);
  } else if (newDis > oldDis && diff > 6) {
    gain = 1.0f;
//    Music.setGain1(1.0f);
    usbMIDI.sendNoteOn(64, 127, 1);
  } 
  gain = gain * decay;
  Music.setGain(gain);
  xA = newxA;
  xB = newxB; 
}

//////////////////////////////T3 ////////////////////////////////////////

void freqT3A(){
  int newxA = analogRead(A1);
  int newxB = analogRead(A9);
  int newDis = newxA + newxB;

  oldDis = xA + xB;

  int diff = abs(newDis - oldDis);
  if (newDis == oldDis || diff <= 6){
//    Music.setGain1(0.0f);
  } else if (newDis < oldDis && diff > 6) {
//    Music.setGain1(1.0f);
    gain = 1.0f;
    usbMIDI.sendNoteOn(62, 127, 1);
  } else if (newDis > oldDis && diff > 6) {
    gain = 1.0f;
//    Music.setGain1(1.0f);
    usbMIDI.sendNoteOn(64, 127, 1);
  } 
  gain = gain * decay;
  Music.setGain(gain);
  xA = newxA;
  xB = newxB; 
}

void freqT3B(){
  int newxA = analogRead(A1);
  int newxB = analogRead(A9);
  int newDis = newxA + newxB;

  oldDis = xA + xB;

  int diff = abs(newDis - oldDis);
  if (newDis == oldDis || diff <= 6){
//    Music.setGain1(0.0f);
  } else if (newDis < oldDis && diff > 6) {
//    Music.setGain1(1.0f);
    gain = 1.0f;
    usbMIDI.sendNoteOn(62, 127, 1);
  } else if (newDis > oldDis && diff > 6) {
    gain = 1.0f;
//    Music.setGain1(1.0f);
    usbMIDI.sendNoteOn(64, 127, 1);
  } 
  gain = gain * decay;
  Music.setGain(gain);
  xA = newxA;
  xB = newxB; 
}
