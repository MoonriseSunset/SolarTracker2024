#include <Arduino.h>

const int spacing = 400;
const int longspacing = spacing *3;

const int Red = 8;
const int Green = 9;
const int Blue = 10;

int r = 0;
int g = 0;
int b = 0;

int step = 10;

void dot(){
  digitalWrite(Red, HIGH);
  delay(spacing);
  digitalWrite(Red, LOW);
  delay(spacing);
}

void dash(){
  digitalWrite(Red, HIGH);
  delay(longspacing);
  digitalWrite(Red, LOW);
  delay(spacing);
}


void setup() {
  pinMode(Red, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(Blue, OUTPUT);

}

void loop() {
  while(r<255){
    analogWrite(Red, r);
    delay(step);
    r++;
  }
  while(g<255){
    analogWrite(Green, g);
    delay(step);
    g++;
  }
  while(b<255){
    analogWrite(Blue, b);
    delay(step);
    b++;
  }
  
  while(r>0){
    analogWrite(Red, r);
    delay(step);
    r--;
  }
  while(g>0){
    analogWrite(Green, g);
    delay(step);
    g--;
  }
  while(b>0){
    analogWrite(Blue, b);
    delay(step);
    b--;
  }
}