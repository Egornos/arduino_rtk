#include "Wheel.h"

Wheel::Wheel(
    float radius,
    uint8_t number, 
    unsigned int pinA,
    unsigned int pinB,
    uint8_t pwm_moving_threshold=40,
    bool isClockwise = false){

    this->radius = radius;
    this->motor = new Motor(number, pwm_moving_threshold);
    this->encoder = new Encoder(pinA, pinB, isClockwise);
    currentAngle = 0;
    currentAngularVelocity = 0;
    currentLinearVelocity = 0;
    lastTime = micros();
}

Wheel::~Wheel() {
    delete motor;
    delete encoder;
}

void Wheel::update() {
    unsigned long now = micros();
    double nowAngle = encoder->getAngle();
    double dt = (now - lastTime) / 1000000.0; // В секунды
    double angleDiff = nowAngle - currentAngle;

    while (angleDiff > M_PI) angleDiff -= TWO_PI;
    while (angleDiff < -M_PI) angleDiff += TWO_PI;

    if (dt > 0.0001 && dt < 0.1) {
        currentAngularVelocity = angleDiff / (dt);
        currentLinearVelocity = currentAngularVelocity * radius / 1000; // В м/с
    }

    currentAngle = nowAngle;
    lastTime = now;
}

void Wheel::setMotorControl(float control) {
    motor->setMotorControl(control);
}
void Wheel::triggerA() {
    encoder->triggerA();
}
void Wheel::triggerB() {
    encoder->triggerB();
}
void Wheel::reset() {
    encoder->reset();
}

double Wheel::getAngle() {
    return currentAngle;
}
double Wheel::getAngularVelocity() {
    return currentAngularVelocity;
}
double Wheel::getLinearVelocity() {
    return currentLinearVelocity;
}

