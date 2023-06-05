
/*
 TURNTABLE TEST PROGRAM

 This program drives a 28BYJ-48 unipolar stepper motor with UNL2003 quad darlington driver.
 The number of steps in a full rotation is calculated to be:
 - Basic stepper: 32 
 - Stepper internal gearing: 63.68395
 - turntable gearing: 5.66666....  (85:15)

 This program uses the Arduino stepper library and runs on a Particle Photon. Photon pins
 D2, D3, D4 and D5 are wired to stepper motor driver IN1, IN2, IN3 and IN4, respectively, through
 3.3 volt to 5 volt converters (SN74HCT125N).

 Note that for these unipolar stepper motors to work, the motor lead sequnce to the library
 constructor must be IN1, IN3, IN2 and IN4, that this exact sequence.

 The main purpose of this test program is to test proper control of the stepper and assess
 the maximum turntable speed that can be achieved.  The parameter to set the speed of stepping
 is the global constant "delayTime" (value in milliseconds).  

 The program turns the turntable one full revolution clockwise and then one full revolution
 counter-clockwise with a 500 ms delay between direction reversals.  The program repeats 
 indefinitely.

  version 1.1; 6/5/2023;  Added hall effect sensor and home the platen on each loop.
  version 1.0, 5/29/2023:  Initial release for testing

 (c) 2023; by: Bob Glicksman, Jim Schrempp, Team Practical Projects
 All rights reserved.

 */

#include <Stepper.h>

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);

const int stepsPerRevolution = 2038;  // not needed in this test code
const int delayTime = 2000;  // The smallest delay that the stepper will work (in microseconds))!
const int stepsInOneDirection = 11548; // 32 * 63.68395 * 5.6666...
const int stepsForNextSlot = 722; // 1/16 of the way around

// initialize the stepper library, sequence is IN1, IN3, IN2, IN4 on pins D2 through D5:
Stepper myStepper(stepsPerRevolution, D2, D4, D3, D5);  // note the pin sequence in the constructor!

void setup() {
  // the stepper library does all of the needed pinMode() stuff for the stepper.
  pinMode(A0, INPUT); // Pin to read the Hall Effect Sensor for home position
  
}

void loop() {
  // first thing - home the platen
  seekHome();
  delay(2000);  // pause to indicate that we are homed

  // step forward for one slot:
  for(int i = 0; i < stepsForNextSlot; i++)  {
    myStepper.step(1);
    delayMicroseconds(delayTime);
  }
  // pause
  delay(500);

// step forward for one slot:
  for(int i = 0; i < stepsForNextSlot; i++)  {
    myStepper.step(1);
    delayMicroseconds(delayTime);
  }
  // pause
  delay(500);  

  // step backward for one slot:
  for(int i = 0; i < stepsForNextSlot; i++)  {
    myStepper.step(-1);
    delayMicroseconds(delayTime);
  }
  // pause before homing
  delay(500);

}

// function to home the sensor
//  The home position is where the Hall Sensor output goes LOW
void seekHome() {
  while (digitalRead(A0) == HIGH) {  // the position is not home, so step
    myStepper.step(1);  // take one step clockwise
    delayMicroseconds(delayTime);
  }

  // we are at the home position
  return;
} // end of seekHome()

