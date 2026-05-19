#include "Sweepers.h"


Sweepers::Sweepers(unsigned int pinLeft, unsigned int pinRight)
 : pinLeft(pinLeft), pinRight(pinRight) 
{
    lastTime = micros();
    servoLeft.attach(pinLeft);
    servoRight.attach(pinRight);
    servoLeft.write(0); // сразу в "выкл" позицию
    servoRight.write(0);
    lastStepTime = millis(); 
}
Sweepers::~Sweepers() 
{   // Отключаем серво при удалении объекта (на всякий)
    servoLeft.detach();
    servoRight.detach();
}

void Sweepers::start_stop(bool is_active) 
{
    this->is_active = is_active;
    if (!is_active) 
    {
    //    servoLeft.write(180);
    //    servoRight.write(180);
    //} else {
    //    servoLeft.write(0);
    //    servoRight.write(0);
    //}

        // При выключении сразу возвращаем в 0
        servoLeft.write(0);
        servoRight.write(0);
        currentAngle = 0;
        direction = 1;
    }
}

void Sweepers::update() {
    //unsigned long now = micros();
    //if(now - lastTime >= T) {
       // lastTime = now;
       // pwm = (pwm + increment) % 101;
    //}
    if (!is_active) return; // Если выключено - ничего не делаем
    
    unsigned long now = millis();
    // Проверяем, прошло ли время для следующего шага
    if (now - lastStepTime >= STEP_DELAY_MS) {
        lastStepTime = now;
        
        // Меняем угол
        currentAngle += direction;
        
        // Если достигли края - меняем направление
        if (currentAngle >= ANGLE_MAX) {
            currentAngle = ANGLE_MAX;
            direction = -1;
        } else if (currentAngle <= ANGLE_MIN) {
            currentAngle = ANGLE_MIN;
            direction = 1;
        }

        servoLeft.write(currentAngle);
        servoRight.write(currentAngle);
    }   
}
