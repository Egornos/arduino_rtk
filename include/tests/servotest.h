#pragma once
#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("Hardware PWM servo test (pin 9)");

    // Настройка пина 9 как выход
    pinMode(9, OUTPUT);

    // === Настройка таймера 1 для аппаратного ШИМ (50 Гц) ===
    TCCR1A = 0;
    TCCR1B = 0;
    // Режим Fast PWM с TOP = ICR1, неинвертирующий вывод на OC1A (пин 9)
    TCCR1A = (1 << WGM11) | (1 << COM1A1);
    // Предделитель 8, режим 14 (WGM13=1, WGM12=1)
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
    ICR1 = 39999; // период 20 мс (50 Гц)

    // Диапазоны для углов (импульс 0.5–2.5 мс)
    const int PWM_MIN = 1000;   // 0°
    const int PWM_MID = 3000;   // 90° (1.5 мс)
    const int PWM_MAX = 5000;   // 180°

    Serial.println("Position: 0°");
    OCR1A = PWM_MIN;
    delay(2000);

    Serial.println("Position: 90°");
    OCR1A = PWM_MID;
    delay(2000);

    Serial.println("Position: 180°");
    OCR1A = PWM_MAX;
    delay(2000);

    Serial.println("Position: 0° again");
    OCR1A = PWM_MIN;
    delay(2000);

    Serial.println("Test finished. Servo should have moved smoothly.");
}

void loop() {
    // ничего не делаем
}