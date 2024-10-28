/*
Solar Tracker Code Prototype

Written by Adam Esch

Last edited: 10/28/2024

TODO:
- Add Code for secondary axes

*/

//PIO Setup
#include <Arduino.h>

//Library Setup
#include <Servo.h>

//Vars:
int direction = 0;
int index = 0;

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

float getData(int pin,int samples){
  float result = 0.0;

  for (int i = 0; i < samples; i++){
    result += analogRead(pin);
  }

  return result / samples;
}

void findSun(int delayTime = 100,int samples = 100){

  float pr1Max = 0.0;
  float pr2Max = 0.0;
  float sensorSum = 0.0;
  float maxIntensity = 0.0;
  int xyThetaRef = 0;

  for(int xyTheta = servoMin; xyTheta < servoMax; xyTheta += stepSize){
    pr1Max = getData(pr1, samples);
    pr2Max = getData(pr2, samples);

    sensorSum = pr1Max + pr2Max;

    if(sensorSum > maxIntensity){
      maxIntensity = sensorSum;
      xyThetaRef = xyTheta;
    }
    xy.write(xyTheta);
    delay(delayTime);
  }

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
  delay(5000);

  findSun(100,100);
  
}

//Now do nothing, for now
void loop() {
}