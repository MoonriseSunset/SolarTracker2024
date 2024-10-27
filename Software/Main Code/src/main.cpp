/*
Solar Tracker Code Prototype

Written by Adam Esch

Last edited: 10/22/2024

TODO:
- Add Code for secondary photoresistor

*/

//PIO Setup
#include <Arduino.h>

//Library Setup
#include <Servo.h>

//Vars:
int direction = 0;
int index = 0;

const int stepSize = 10; //In degrees

int maxIntensity = -1;
int maxIndex = 0;
int intermediate = 0;


//Pins:
const int servoPin = 9;
const int sensorPin = A0;

//Servo Setup
const int servoMin = 0;
const int servoMax = 180;

Servo s;

//Setting up array for 
const int roughSteps = (servoMax - servoMin) / stepSize;

int roughData[roughSteps];

int firstPass[roughSteps];
int secondPass[roughSteps];

void setup() {
  //Pin Setup
  pinMode(servoPin, OUTPUT);
  pinMode(sensorPin, INPUT);

  //Servo Startup
  s.attach(servoPin);

  //First Sensing Pass from 0 to max angle
  while(direction <= servoMax){
    s.write(direction);
    delay(50);
    firstPass[index] = analogRead(sensorPin);

    index++;
    direction += stepSize;
  }

  //Second Sensing Pass from max angle to 0
  while(direction >= servoMin){
    s.write(direction);
    delay(50);

    secondPass[index] = analogRead(sensorPin);

    index--;
    direction -= stepSize;
  }

  //Processing Loop, averages light intensity between first and second pass and finds maximum
  for(int i = 0; i < roughSteps; i++){
    //Averaging intensities
    intermediate = (firstPass[i] + secondPass[i]) / 2;

    //Finding maximum
    if(intermediate > maxIntensity){
      maxIntensity = intermediate;
      maxIndex = i;
    }
  }
  
  //Now that we have the maximum, move assembly to the max angle.
  s.write(maxIndex * stepSize);
}

//Now do nothing
void loop() {
}