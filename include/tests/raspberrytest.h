#pragma once
#include "Robot.h"
#include "SerialReader.h"
#include <PinChangeInterrupt.h>

/*
Этот код запускает моторы и выводит одометрию.
Всё запускается через иерархию классов, её надо проследить.
*/

Robot robot = Robot();

void updateLWA() { robot.left_triggerA(); }
void updateLWB() { robot.left_triggerB(); }
void updateRWA() { robot.right_triggerA(); }
void updateRWB() { robot.right_triggerB(); }

void setup() {
    Serial.begin(115200);
    robot.reset();
    
    // Это триггеры, запускают функцию, при появлении напряжения на пине
    attachInterrupt(digitalPinToInterrupt(robot.getLeftPinA()), // Указываем пин, который будем проверять
        updateLWA, // Указываем вызываемую функцию
        RISING /* Указываем на что будет реагировать триггер, в данном случае на увеличение напряжения */ );
    attachInterrupt(digitalPinToInterrupt(robot.getLeftPinB()), updateLWB, RISING);
    attachPCINT(digitalPinToPCINT(robot.getRightPinA()), updateRWA, RISING);
    attachPCINT(digitalPinToPCINT(robot.getRightPinB()), updateRWB, RISING);
    /* 
    Также триггер можно настроить на реакцию на изменение или уменьшение напряжения.
    В гите от Ислама был триггер на увеличение, решил так и оставить.
    */
}
// Переменные для корректных выводов
unsigned long lastUpdate = 0;
unsigned long lastPrint = 0;
const double DT = 0.02;
const double PRINT_DT = 0.1;

void loop() {
    unsigned long now = millis();
    
    // Запускаем обновление одометрии и запускаем моторы, не чаще чем раз в DT секунд
    if (now - lastUpdate >= DT * 1000) {
        readSerialData();
        lastUpdate = now;
        robot.update(); // Обновление информации
        robot.setMotors(targetLeft /*Левый*/, targetRight /*Правый*/); // Подача напряжений на моторы, от -1 до 1
    }
    
    // Делаем вывод одометрии не чаще чем PRINT_DT секунд
    if (now - lastPrint >= PRINT_DT * 1000) {
        lastPrint = now;
        double x, y, theta;
        robot.getPosition(x, y, theta);
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.print(",");
        Serial.println(theta);
    }
}