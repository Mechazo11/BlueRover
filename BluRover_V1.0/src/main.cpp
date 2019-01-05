// BluRover
// Version 1.0
// Author: Azmyin Md. Kamal
// Date: 02/08/2018
// Sketch automatically detects which com port to use
//
// This sketch will not be used as the sparkfun board is causing a lot of problems with various hardwares used

// Summary
// Board: Sparkfun Pro Micro 5V/16Mhz clone
// Equipment PARALLEX 4pin Sonar, HC05 bluetooth module, 5V active buzzer
// This HC05 is configured as
// Role - Slave, Baud Rate - 38400, Connection - Any master
// Passkey - 1234
// Bluetooth name: ROVER

// Connection Scheme
// Right motor (Bank B), OUTC, OUTD, INC-A0, IND-A1, ENB- ~9
// Left motor (Bank A), OUTA, OUTB, INA-A2, INB-A3, ENA- ~10
// Sonar Vcc-5v, GND-GND, Trigger-11, Echo-12, Library - NewPing
// Buzzer Vcc- ~3, GND-GND, Signal- Not required, doesnt work
// HC05 Module: RX-1, TX-0, GND-GND, Vcc-5V, En-5V

// Notes
// The sonar works best for flat surface.


#include <Arduino.h>

#define buzzer 3
#define INC 14
#define IND 15
#define ENB 9
#define INA 16
#define INB 17
#define ENA 10

int global_speed = 150; // Control PWM to motors
int forward_speed = 225; // Just a different speed for going forward fast
int state = 0; // Record value from remote

void pin_set(); // sets all required pins to their right states
void forward(); // All wheel C.W
void reverse(); // All wheel C.C.W
void turn_right(); // Right-C.w, Left-C.C.W
void turn_left(); // Right-C.C.w, Left-C.W
void stop(); // All wheel stop

void setup() {
Serial.begin(38400); // Must match configuration of slave HC05
pin_set();
}

void loop() {
  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
      state = Serial.read(); // Reads the data from the serial port
   }
   if (state == '1')
    {
      forward();
    }
    else if (state == '2')
    {
      reverse();
    }
    else if (state == '3')
    {
      turn_right();
    }
    else if (state == '4')
    {
      turn_left();
    }
      else // Adding condition here throws error
      {
        stop();
      }
}// End of void loop()

void forward(){
  digitalWrite(INC, LOW); digitalWrite(IND, HIGH); analogWrite(ENB,forward_speed);
  digitalWrite(INA, HIGH); digitalWrite(INB, LOW); analogWrite(ENA,forward_speed);
}
void reverse(){
  digitalWrite(INC, HIGH); digitalWrite(IND, LOW); analogWrite(ENB,global_speed);
  digitalWrite(INA, LOW); digitalWrite(INB, HIGH); analogWrite(ENA,global_speed);
}
void turn_right() {
  digitalWrite(INC, LOW); digitalWrite(IND, HIGH); analogWrite(ENB,global_speed);
  digitalWrite(INA, LOW); digitalWrite(INB, HIGH); analogWrite(ENA,global_speed);
}
void turn_left(){
  digitalWrite(INC, HIGH); digitalWrite(IND, LOW); analogWrite(ENB,global_speed);
  digitalWrite(INA, HIGH); digitalWrite(INB, LOW); analogWrite(ENA,global_speed);
}
void stop(){
  digitalWrite(INC, LOW); digitalWrite(IND, LOW); analogWrite(ENB,0);
  digitalWrite(INA, LOW); digitalWrite(INB, LOW); analogWrite(ENA,0);
}

void pin_set() {
pinMode(buzzer, OUTPUT);
pinMode(INC, OUTPUT);
pinMode(IND, OUTPUT);
pinMode(ENB, OUTPUT);
pinMode(INA, OUTPUT);
pinMode(INB, OUTPUT);
pinMode(ENA, OUTPUT);

digitalWrite(buzzer, LOW);
digitalWrite(INC, LOW);
digitalWrite(IND, LOW);
digitalWrite(ENB, LOW);
digitalWrite(INA, LOW);
digitalWrite(INB, LOW);
digitalWrite(ENA, LOW);
}
