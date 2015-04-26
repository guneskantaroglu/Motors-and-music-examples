#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

float k = 15.3f; // spring coefficient (stiffness)
float m = 50.0f; // mass
float d = 7.0f;  // damping coefficient

float x;
float v;
float f;

long tick = 0;
int last_pos = 0;

int c = 0;

void setup() {
  
  Music.init();
  MotorA.init();
  tick = millis();
  x = analogRead(A1);
}

void loop() {

  long tick_now = millis();
  float dt = (float)(tick_now - tick) / 100.0f;

  int current_pos = analogRead(A1);

  f = k * (current_pos - x) - (d * v);
  v += (f / m) * dt;
  x += v * dt;

  tick = millis();

  int t = map(f, -5000, 5000, -512, 512);   // re-mapping the force to a (valid) torque value
  //t = constrain(t, -512, 512);
  MotorA.torque(t);
  
  int freq = map(abs(f), 0, 10000, 50, 1500);
  Music.setFrequency(freq);

  c++;
  if ( c % 20 == 0) {
    Serial.println(analogRead(A0));
  }

}











