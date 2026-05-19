#include <Arduino.h>
#include <Servo.h>

class Sweepers
{
private:
    Servo servoLeft, servoRight;  // create servo object to control a servo

    float T = 10;
    int increment = 1;
    bool is_active = false;
    unsigned int pinLeft, pinRight;
    unsigned long lastTime;
    int pwm = 0;

    // Для качания с 0 до 180
    int currentAngle = 0; // Текущий угол
    int direction = 1; // 1 = увеличиваем, -1 = уменьшаем 
    const int ANGLE_MIN = 0; // Минимальный угол
    const int ANGLE_MAX = 180; // Максимальный угол
    const unsigned long STEP_DELAY_MS = 50; // Скорость качания (меньше = быстрее)
    unsigned long lastStepTime = 0;

public:
    Sweepers(unsigned int pinLeft, unsigned int pinRight);
    ~Sweepers();

    void start_stop(bool is_active);
    void update();
};