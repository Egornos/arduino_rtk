#include "Odometry.h"

Odometry::Odometry(float base) {
    this->base = base;
    leftLinVel = 0.0;
    rightLinVel = 0.0;
    lastTime = micros();
}
Odometry::~Odometry() {}

void Odometry::update(double newLeftLinVel, double newRightLinVel) {
    unsigned long now = micros();
    double dt = (now - lastTime) / 1000000.0; // В секунды

    if (dt > 0.0001 && dt < 0.1) {
        double dLeft = leftLinVel * dt;
        double dRight = rightLinVel * dt;

        double deltaTheta = (dRight - dLeft) / base *1000;
        double deltaCenter = (dRight + dLeft) / 2.0;

        x += deltaCenter * cos(theta + deltaTheta / 2.0);
        y += deltaCenter * sin(theta + deltaTheta / 2.0);
        theta += deltaTheta;

        if (theta > M_PI) {
            theta -= 2.0 * M_PI;
        } else if (theta < -M_PI) {
            theta += 2.0 * M_PI;
        }
    }

    leftLinVel = newLeftLinVel;
    rightLinVel = newRightLinVel;
    lastTime = now;
}

void Odometry::getOdometry(double &x, double &y, double &theta) {
    x = this->x;
    y = this->y;
    theta = this->theta;
}

void Odometry::reset() {
    x = 0;
    y = 0;
    theta = 0;
}