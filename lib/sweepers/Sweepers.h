#pragma once
#include <Arduino.h>
#include <Servo.h>

class Sweepers
{
private:
    Servo servo; // Только одна серва
    unsigned int pin; // Только один пин
    
    bool is_active = false;
    bool is_attached = false; // Флаг, подключена ли серва
    int currentAngle = 0;
    int direction = 1; 

    const int ANGLE_MIN = 0;
    const int ANGLE_MAX = 180;
    const unsigned long STEP_DELAY_MS = 20; 
    unsigned long lastStepTime = 0;

    int minPulseUs; 
    int maxPulseUs;

public:
    // Конструктор принимает только ОДИН пин
    Sweepers(unsigned int pin, int minUs = 500, int maxUs = 2400);
    
    // Новый метод для инициализации
    void begin();
    
    ~Sweepers();
    
    void start_stop(bool is_active);
    void update();
};