/*
Solar Tracker Code Prototype

Written by Adam Esch

Last edited: 10/27/2024

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

void findSun(int delayTime = 100){

  float pr1Max = 0.0;
  //float pr2Max = 0.0;
  float maxIntensity = 0.0;
  int xyThetaRef = 0;

  for(int xyTheta = servoMin; xyTheta < servoMax; xyTheta += stepSize){
    pr1Max = getData(pr1, 100);
    //pr2Max = getData(pr2, 10);

    if(pr1Max > maxIntensity){
      maxIntensity = pr1Max;
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

  //Servo Startup
  xy.attach(xyServo);
  //z.attach(zServo);

  //Homing
  xy.write(servoMin);
  delay(5000);

  findSun();
  
}

//Now do nothing
void loop() {
}