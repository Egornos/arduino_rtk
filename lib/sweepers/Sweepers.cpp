#include "Sweepers.h"


Sweepers::Sweepers(unsigned int pinLeft, unsigned int pinRight) : pinLeft(pinLeft), pinRight(pinRight) {
    lastTime = micros();
}
Sweepers::~Sweepers() {}

void Sweepers::start_stop(bool is_active) {
    this->is_active = is_active;
}
void Sweepers::update() {
    unsigned long now = micros();
    if(now - lastTime >= T) {
        lastTime = now;
        pwm = (pwm + increment) % 101;
    }
    
}
