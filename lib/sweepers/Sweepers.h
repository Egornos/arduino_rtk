#include <Arduino.h>

class Sweepers
{
private:
    float T = 10;
    int increment = 1;
    bool is_active = false;
    unsigned int pinLeft, pinRight;
    unsigned long lastTime;
    int pwm = 0;
public:
    Sweepers(unsigned int pinLeft, unsigned int pinRight);
    ~Sweepers();

    void start_stop(bool is_active);
    void update();
};