
/*
 Stepper Motor Control - one step at a time

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.

 The motor will step one step at a time, very slowly.  You can use this to
 test that you've got the four wires of your stepper wired to the correct
 pins. If wired correctly, all steps should be in the same direction.

 Use this also to count the number of steps per revolution of your motor,
 if you don't know it.  Then plug that number into the oneRevolution
 example to see if you got it right.

 Created 30 Nov. 2009
 by Tom Igoe

 */

#include <Stepper.h>

const int stepsPerRevolution = 2038;
const int delayTime = 2;
const int stepsInOneDirection = 12228; // 20138 * 6

// initialize the stepper library, sequence is IN1, IN3, IN2, IN4 on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, D0, D2, D1, D3);

int stepCount = 0;         // number of steps the motor has taken

void setup() {
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  // step forward 1 rev:
  for(int i = 0; i < stepsInOneDirection; i++)  {
    myStepper.step(1);
    delay(delayTime);
  }
  // pause beforte reversing
  delay(500);

  // step backward 1 rev
  for(int i = 0; i < stepsInOneDirection; i++)  {
    myStepper.step(-1);
    delay(delayTime);
  }
  // pause beforte reversing
  delay(500);

}

