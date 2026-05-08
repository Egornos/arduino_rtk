#include <AFMotor.h>
#include <stdlib.h>

/*
Класс, подающий напряжение на моторы.
Так же взят из репозитория, но менялся под нас.
*/

class Motor
{
private:
  AF_DCMotor *motor1;
  AF_DCMotor *motor2;
  uint8_t pwm_moving_threshold;
  int sendedPWM;
public:
  // Конструктор принимает номер мотора и минимальное напряжение, подаваемое на мотор.
  Motor(uint8_t number, uint8_t pwm_moving_threshold=40);
  ~Motor(); // Деконструктор класса

  /* 
  Устанавливает переменную, из которой потом будет рассчитан ШИМ.
  Если смотреть по формуле, то подавать надо [-1; 1], но в гите коммент по другому пишет...
  */
  void setMotorControl(float control); // [-255; 255] (Исходный ком)
  void setPWMMovingThreshold(uint8_t pwmThreshold); // [0; 255] (Исходный ком)

  // По сути исполнительный класс, остальные функции видимо для отладки.
  uint8_t getPWMMovingThreshold(); // [0; 255] (Исходный ком)
  int getSendedPWM();
};