#include "sweepers.h"


sweepers::sweepers(unsigned int pinLeft, unsigned int pinRight) : pinLeft(pinLeft), pinRight(pinRight) {
    lastTime = micros();
}
sweepers::~sweepers() {}

void sweepers::start_stop(bool is_active) {
    this->is_active = is_active;
}
void sweepers::update() {
    unsigned long now = micros();
    if(now - lastTime >= T) {
        lastTime = now;
        pwm = (pwm + increment) % 101;
    }
    
}
