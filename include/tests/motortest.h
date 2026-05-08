#include <Arduino.h>
#include "Motor.h"

/*
Отдельно запуск моторов.
У нас моторы подключены к M3 - правый и M4 - левый
*/

Motor motor_l(4);
Motor motor_r(3);

void setup() {
    Serial.begin(38400);
}

void loop() {
    motor_l.setMotorControl(0.0);
    motor_r.setMotorControl(0.0);
}