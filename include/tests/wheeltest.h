#include <Arduino.h>
#include "Wheel.h"
#include "config.h"
#include <PinChangeInterrupt.h>
   
Wheel leftWheel = Wheel(WHEEL_RADIUS, 4, ENC_MOTOR4_PINA, ENC_MOTOR4_PINB);
Wheel rightWheel = Wheel(WHEEL_RADIUS, 3, ENC_MOTOR3_PINA, ENC_MOTOR3_PINB);

void updateLWA() { leftWheel.triggerA(); }
void updateLWB() { leftWheel.triggerB(); }
void updateRWA() { rightWheel.triggerA(); }
void updateRWB() { rightWheel.triggerB(); }

void setup() {
    Serial.begin(115200);
    pinMode(ENC_MOTOR4_PINA, INPUT_PULLUP);
    pinMode(ENC_MOTOR4_PINB, INPUT_PULLUP);
    pinMode(ENC_MOTOR3_PINA, INPUT_PULLUP);
    pinMode(ENC_MOTOR3_PINB, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ENC_MOTOR4_PINA), // Указываем пин, который будем проверять
        updateLWA, // Указываем вызываемую функцию
        RISING /* Указываем на что будет реагировать триггер, в данном случае на увеличение напряжения */ );
    attachInterrupt(digitalPinToInterrupt(ENC_MOTOR4_PINB), updateLWB, RISING);
    attachPCINT(digitalPinToPCINT(ENC_MOTOR3_PINA), updateRWA, RISING);
    attachPCINT(digitalPinToPCINT(ENC_MOTOR3_PINB), updateRWB, RISING);
}

void loop() {
    rightWheel.update();
    leftWheel.update();
    Serial.print(leftWheel.getAngle() * WHEEL_RADIUS / 1000);
    Serial.print(',');
    Serial.println(rightWheel.getAngle() * WHEEL_RADIUS / 1000);
}