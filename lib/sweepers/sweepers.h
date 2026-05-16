#include <Arduino.h>

class sweepers
{
private:
    float T = 10;
    int increment = 1;
    bool is_active = false;
    unsigned int pinLeft, pinRight;
    unsigned long lastTime;
    int pwm = 0;
public:
    sweepers(unsigned int pinLeft, unsigned int pinRight);
    ~sweepers();

    void start_stop(bool is_active);
    void update();
};