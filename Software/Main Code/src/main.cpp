/*
Solar Tracker Code Prototype

Written by Adam Esch

Last edited: 10/29/2024

PLATFORMIO VERSION

TODO:
- Add Code for secondary axes

*/

//PIO Setup
#include <Arduino.h>

//Library Setup
#include <Servo.h>

//Variables
const int stepSize = 10; //In degrees

//Pins:
const int xyServo = 9;
//const int zServo = 10;

const int pr1 = A0;
const int pr2 = A1;

//Servo Setup
const int servoMin = 0;
const int servoMax = 180;

Servo xy;
//Servo z;


// Read our photoresistor, specified by the pin argument, a set number of times and then average the value so we get better data
float getData(int pin,int samples){
  float result = 0.0;

  for (int i = 0; i < samples; i++){
    result += analogRead(pin);
  }

  return result / samples;
}

// Primary Function
void findSun(int delayTime = 100,int samples = 100){

  float pr1Max = 0.0;
  float pr2Max = 0.0;

  float sensorSum = 0.0;

  float maxIntensity = 0.0;

  int xyThetaRef = 0;

  // Primary Loop, we set the servo to 0 degrees, defined by servoMin, and step the servo by a set number of degrees defined by stepSize, till we hit 180 degrees (servoMax)
  for(int xyTheta = servoMin; xyTheta < servoMax; xyTheta += stepSize){

    // For each degree step that we do, read the photoresistors with the previous function that gives us better data
    pr1Max = getData(pr1, samples);
    pr2Max = getData(pr2, samples);

    // Sum the sensor data
    sensorSum = pr1Max + pr2Max;

    // To save on memory, we check to see if the combined sensor data is higher than previous readings (thus indicating being in brighter light)
    // If we find a new highest value, the program stores the angle so we can return back to it later
    if(sensorSum > maxIntensity){
      maxIntensity = sensorSum;
      xyThetaRef = xyTheta;
    }

    //Step the servo and then wait a little (the waiting is for effect, realistically it doesn't really need such a long delay)
    xy.write(xyTheta);
    delay(delayTime);
  }

  // After the loop, the program now has an angle stored where the arduino sensed the highest intensity light, so let's go to it
  xy.write(xyThetaRef);

}

void setup() {

  //Pin Setup
  pinMode(xyServo, OUTPUT);
  //pinMode(zServo, OUTPUT);

  pinMode(pr1, INPUT);
  pinMode(pr2, INPUT);

  //Servo Startup
  xy.attach(xyServo);
  //z.attach(zServo);

  //Homing
  xy.write(servoMin);

  //Wait for a little so people can get out of the way so the tracker can run unobstructed
  delay(5000);

  //Run our rough finding function
  findSun(100,100);

  //fineTuning();
  
}

//Now do nothing, for now
void loop() {
}