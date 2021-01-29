
#include <Arduino.h>
#include "IotHome.h"

IotHome::IotHome() {}

void IotHome::init() {
  /*pinMode(PIN_1, OUTPUT);
	pinMode(PIN_2, OUTPUT);
  pinMode(PIN_6, OUTPUT);*/
}

void IotHome::setValue(int pin, int value) {
	analogWrite(pin, value);
}
