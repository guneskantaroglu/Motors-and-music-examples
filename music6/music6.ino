#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

float k = 5.3f; //spring elasticity
float m = 1.0f; //mass
float d = 0.0f; //damping coefficient

float x; //virtual position
float v; //velocity
float f; //force (f=ma)

long tick = 0;
int last_pos = 0;

int c = 0; //counter

void setup() {

  MotorA.init();
  Music.init();
  tick = millis(); //now
  last_pos = analogRead(A1);

}


void loop() {

  long tick_now = millis();

  float dt = (float)(tick_now - tick) / 100.0f; //gives us the difference in time

  int current_pos = analogRead(A1);

  int dx = last_pos - current_pos; // difference in position

  f = k * (dx - x) - (d * v);
  v += (f / m) * dt; // velocity is a derivative
  x += v * dt;

  MotorA.torque(f);
  
  set_freq(v);

  tick = millis(); // update tick to now

  //last_pos = current_pos;

  c++;

  if (c % 1000 == 0) {
    Serial.println(f);
    Serial.println(v);
    Serial.println(x);
    Serial.println("------");


  }


}

void set_freq(float vel) {

  float vel_amp = abs(vel); // only absolute values
  float freq = map(vel_amp, 0, 6000, 100, 1500);

  Music.setFrequency(freq);

}




