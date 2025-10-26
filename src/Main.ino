#define UBRRH

#include <Arduino.h>
#include "Test.hpp"

#define PIN_MOTOR 9
#define PIN_BUTTON 11

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_MOTOR, OUTPUT);

  pinMode(PIN_BUTTON, INPUT);
  digitalWrite(PIN_BUTTON, HIGH);

  test();
}

void loop() {
  // put your main code here, to run repeatedly:
  //analogWrite(PIN_MOTOR, 255);
  if (digitalRead(PIN_BUTTON) == LOW) {
    analogWrite(PIN_MOTOR, 255);
  } else {
    analogWrite(PIN_MOTOR, 0);
  }
}
