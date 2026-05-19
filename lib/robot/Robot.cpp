#include "Robot.h"

Robot::Robot() {
    this->leftWheel = new Wheel(WHEEL_RADIUS, 4, ENC_MOTOR4_PINA, ENC_MOTOR4_PINB);
    this->rightWheel = new Wheel(WHEEL_RADIUS, 3, ENC_MOTOR3_PINA, ENC_MOTOR3_PINB);
    this->odometry = new Odometry(ROBOT_BASE);
    this->sweepers = new Sweepers(SERVO1, SERVO2);
    leftPinA = ENC_MOTOR4_PINA;
    leftPinB = ENC_MOTOR4_PINB;
    rightPinA = ENC_MOTOR3_PINA;
    rightPinB = ENC_MOTOR3_PINB;

}
Robot::~Robot(){
    delete leftWheel;
    delete rightWheel;
    delete odometry;
};

void Robot::update() {
    leftWheel->update();
    rightWheel->update();
    odometry->update(leftWheel->getLinearVelocity(), rightWheel->getLinearVelocity());
    odometry->getOdometry(x, y, theta);
    sweepers->update();
}

void Robot::reset() {
    x = 0;
    y = 0;
    theta = 0;
    odometry->reset();
    leftWheel->reset();
    rightWheel->reset();
}

void Robot::getPosition(double &x, double &y, double &theta) {
    x = this->x;
    y = this->y;
    theta = this->theta;
}

void Robot::setMotors(float leftControl, float rightControl) {
    leftWheel->setMotorControl(leftControl);
    rightWheel->setMotorControl(rightControl);
}

void Robot::left_triggerA() {
    leftWheel->triggerA();
}
void Robot::left_triggerB() {
    leftWheel->triggerB();
}
void Robot::right_triggerA() {
    rightWheel->triggerA();
}
void Robot::right_triggerB(){
    rightWheel->triggerB();
}

unsigned int Robot::getLeftPinA() {return leftPinA;}
unsigned int Robot::getLeftPinB() {return leftPinB;}
unsigned int Robot::getRightPinA() {return rightPinA;}
unsigned int Robot::getRightPinB() {return rightPinB;}

void Robot::sweepersActivate(bool is_active) {
    sweepers->start_stop(is_active);
}
