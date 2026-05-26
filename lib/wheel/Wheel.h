#pragma once

#include "Motor.h"
#include "Encoder.h"
#include "PID.h"

/*
Класс объединяющий (реализующий) классы Encoder и Motor.
Через него осуществляется управление двигателем и сбор с него информации.
Так же в этом классе расчитываются угловая и линейная скорости колеса.
*/

class Wheel
{
private:
    float radius; //мм

    Motor *motor;
    Encoder *encoder;
    PID *pid;

    double currentAngle;
    double currentAngularVelocity;
    double currentLinearVelocity;
    float desiredLinearVelocity;
    unsigned long lastTime;
public:
    // Конструктор принимает данные для построения объектов реализуемых классов и радиус колеса в мм.
    Wheel(
        float radius,
        uint8_t number, 
        unsigned int pinA,
        unsigned int pinB,
        uint8_t pwm_moving_threshold=40,
        bool isClockwise = false);
    ~Wheel();

    /* В этой функции расчитываются скорости колеса.
    Для этого считается разница во времени, поэтому эту функцию надо запускать постоянно. */
    void update();
    void setWheelLinearVelocity(float desiredAngularVelocity);

    // Реализация необходимых в дальнейшем функций из прошлых классов.
    void setMotorControl(float control);
    void triggerA();
    void triggerB();
    void reset();

    // Получение данных о колесе.
    double getAngle();
    double getAngularVelocity();
    double getLinearVelocity();
};