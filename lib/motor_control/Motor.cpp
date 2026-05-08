#include "Arduino.h"
#include "Motor.h"

/*
Вот тут главный прикол, по сути, библиотека AF_DCMotor должна управлять моторами,
подключенными к разъёмам М1, М2, М3, М4, но у нас подключены только к М3 и М4.
Через эту библиотеку создаются объекты, через номер разъёма, к которому подключен мотор.
Почему-то, подавая напряжения только на М3 и М4 моторы не крутятся и чтобы запустить,
например, мотор, подключенный к М3, надо подать ещё и на М1.
Почему так? Честно, хз. Эту схему управления я понял быстро и потом часа 3 сидел понимал почему.
Если верить дипсику, то это норм так и должно быть из устройства платы управления.
Вручную через пины пытался, нифига. В целом работает, решил сначала остальное сделать, потом к этому вернуться.
Эта часть работает странно, вроде моторы крутятся, но как-то вяло, как-будто либо не доходит напряжение,
либо моторам плохо. Пока склоняюсь к первому. Возможно надо будет переделать реализацию этого класса.
*/

Motor::Motor(uint8_t number, uint8_t pwm_moving_threshold)
:pwm_moving_threshold(pwm_moving_threshold) {
  // Тут немного математики, чтобы подключались оба разъёма по одному номеру.
  motor1 = new AF_DCMotor((number - 1) % 4 + 1);
  motor2 = new AF_DCMotor((number + 1) % 4 + 1);
}
Motor::~Motor() { delete motor1; delete motor2; }

void Motor::setMotorControl(float control) {
  
  int unclipedPWM = 0;
  // Преобразование control в ШИМ
  if(control!=0.0){
    unclipedPWM= control*(255-pwm_moving_threshold) + copysign(pwm_moving_threshold, control);
  }
  sendedPWM = constrain(unclipedPWM, -255, 255);
  if (abs(sendedPWM)<pwm_moving_threshold+3) {
    motor1->setSpeed(0); // Это подача ШИМ на мотор
    motor1->run(RELEASE); // Это подача сигнала направления вращения
    motor2->setSpeed(0);
    motor2->run(RELEASE); // Никуда
  } else if (sendedPWM > 0) {
    motor1->run(FORWARD); // Вперёд
    motor1->setSpeed(abs(sendedPWM));
    motor2->run(FORWARD);
    motor2->setSpeed(abs(sendedPWM));
  } else {
    motor1->run(BACKWARD); // Назад
    motor1->setSpeed(abs(sendedPWM));
    motor2->run(BACKWARD);
    motor2->setSpeed(abs(sendedPWM));
  }
}

uint8_t Motor::getPWMMovingThreshold(){
  return pwm_moving_threshold;
}

int Motor::getSendedPWM(){
  return sendedPWM;
}