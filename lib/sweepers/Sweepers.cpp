#include "Sweepers.h"

// Конструктор теперь принимает один пин
Sweepers::Sweepers(unsigned int pin, int minUs, int maxUs)
: pin(pin), minPulseUs(minUs), maxPulseUs(maxUs)
{    
    currentAngle = ANGLE_MIN;
    direction = 1;
    lastStepTime = millis();
    is_active = false;
}

void Sweepers::begin() {
    if (!is_attached) {
        servo.attach(pin, minPulseUs, maxPulseUs);
        // Сразу после подключения ставим в 0, чтобы не было рывка
        servo.write(ANGLE_MIN);
        delay(500); // Даем серве 0.5 сек спокойно встать в ноль перед стартом программы
        is_attached = true;
        lastStepTime = millis();
    }
}

Sweepers::~Sweepers()
{   
    if (is_attached) {
        servo.detach();
    }
}

void Sweepers::start_stop(bool isActive)
{
    this->is_active = isActive;
    if (!isActive)
    {
        servo.write(ANGLE_MIN);
        currentAngle = ANGLE_MIN;
        direction = 1;
    }
    else
    {
        lastStepTime = millis();
    }
}

void Sweepers::update()
{
    if (!is_active || !is_attached) return;

    unsigned long now = millis();
    if (now - lastStepTime >= STEP_DELAY_MS)
    {
        lastStepTime = now;
        
        int nextAngle = currentAngle + direction;

        if (nextAngle >= ANGLE_MAX) {
            currentAngle = ANGLE_MAX;
            direction = -1; 
        } else if (nextAngle <= ANGLE_MIN) {
            currentAngle = ANGLE_MIN;
            direction = 1; 
        } else {
            currentAngle = nextAngle;
        }

        servo.write(currentAngle);
    }
}