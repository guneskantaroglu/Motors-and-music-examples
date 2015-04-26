#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

long tick = 0;

int c = 0; // counter

int last_pos = 0; //initialize position

void setup() {

  tick = millis(); //initializing time
  last_pos = analogRead(A1);
  
  Music.init();

}

void loop() {
  long tick_now = millis();
  long dt = tick_now - tick;


  if (dt >= 20) {
    c++;

    int current_pos = analogRead(A1);
    int dx = last_pos - current_pos;
    float vel = (float) dx / (float) dt;
    
    if(abs(vel) >= 1.0) {
      set_freq(vel);
      
    }
    
    if(c % 15 == 0) {
      Serial.println(vel);
    }
    tick = millis(); // resets time
    last_pos = current_pos; // calculates diff all over again

  } // gives it some time to read and calculate

}

void set_freq(float vel) {
 
 float vel_amp = abs(vel); // only absolute values
 float freq = map(vel_amp, 0, 12, 100, 1500); 
 
 Music.setFrequency(freq);
  
}
