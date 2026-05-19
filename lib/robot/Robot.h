#pragma once

#include "Wheel.h"
#include "Odometry.h"
#include "config.h"
#include "Sweepers.h"

/*
Главный класс, собирающий весь конструктор в единое целое.
Через него будем получать информацию и управлять.
Сюда же в последствии надо будет запихнуть управление щётками. Также через классы.
*/

class Robot {
private:
    double x, y, theta;
    unsigned int leftPinA, leftPinB, rightPinA, rightPinB;

    // Объекты классов.
    Wheel *leftWheel;
    Wheel *rightWheel;
    Odometry *odometry;
    Sweepers *sweepers;
public:
    Robot();
    ~Robot();

    // Триггеры энкодеров, функции вызывают друг друга, пока не вызовет внутри объекта encoder.
    void left_triggerA();
    void left_triggerB();
    void right_triggerA();
    void right_triggerB();

    void update(); // Обновляет все одноимённые функции в объектах.
    void reset(); // Сбрасывает во всех функциях.
    void getPosition(double &x, double &y, double &theta); // Передаёт инфу о местоположенни из одометрии.
    void setMotors(float leftControl, float RightControl); // Задаёт управление моторов.
    void sweepersActivate(bool is_active);

    // Возращают пины энкодеров.
    unsigned int getLeftPinA();
    unsigned int getLeftPinB();
    unsigned int getRightPinA();
    unsigned int getRightPinB();
};