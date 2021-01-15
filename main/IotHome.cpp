
#include <Arduino.h>
#include "IotHome.h"

IotHome::IotHome() {}

void IotHome::init() {
  pinMode(PIN_1, OUTPUT);
	pinMode(PIN_2, OUTPUT);
  pinMode(PIN_3, OUTPUT);
  pinMode(PIN_4, OUTPUT);
  pinMode(PIN_5, OUTPUT);
  pinMode(PIN_6, OUTPUT);
  pinMode(PIN_7, OUTPUT);
 
  digitalWrite(PIN_1, LOW);
  digitalWrite(PIN_2, LOW);
  digitalWrite(PIN_3, LOW);
  digitalWrite(PIN_4, LOW);
  digitalWrite(PIN_5, LOW);
  digitalWrite(PIN_6, LOW);
  digitalWrite(PIN_7, LOW);
}

void IotHome::tryOn(int pin) {
	digitalWrite(pin, HIGH);
}

void IotHome::tryOff(int pin) {
	digitalWrite(pin, LOW);
}
