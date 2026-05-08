#include "Arduino.h"

/*
Класс, считающий одометрию и содержащий её.
*/
class Odometry {
private:
    float base;

    double x, y, theta;
    double leftLinVel, rightLinVel;
    unsigned long lastTime;
public:
    // Конструктор принимает размер базы в мм. 
    Odometry(float base);
    ~Odometry();

    /* Получает линейные скорости колёс и считает одометрию.
    Основывается на разности во времени между получением информации.
    Реализовывал немного другой идей, не как на ВПД, так что надо будет проверить на точность. */
    void update(double leftLinVel, double rightLinVel);
    void reset(); // Сброс одометрии.
    void getOdometry(double &x, double &y, double &theta); // Получение одометрии через ссылки.
};