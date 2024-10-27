#include <Arduino.h>

const int pr1 = A0;
const int pr2 = A1;

const int pr1_bias = 0;
const int pr2_bias = -2;

const int sampleTime = 500;

int pr1_data = 0;
int pr2_data = 0;

void setup() {
  
  pinMode(pr1, INPUT);
  pinMode(pr2, INPUT);

  Serial.begin(9600);
  while(!Serial);

}

void loop() {

  pr1_data = analogRead(pr1) + pr1_bias;
  pr2_data = analogRead(pr2) + pr2_bias;

  Serial.print("PR1 Raw: ");
  Serial.println(pr1_data);

  Serial.print("PR1 Voltage: ");
  Serial.print(5.0*pr1_data/1023.0);
  Serial.println("V");

  Serial.println();

  Serial.print("PR2 Raw: ");
  Serial.println(pr2_data);

  Serial.print("PR2 Voltage: ");
  Serial.print(5.0*pr2_data/1023.0);
  Serial.println("V");

  Serial.println();

  delay(sampleTime);

}