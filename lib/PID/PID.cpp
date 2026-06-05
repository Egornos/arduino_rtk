// PID.cpp
#include "PID.h"

PID::PID(float kP, float kI, float kD, float dt)
    : kP(kP), kI(kI), kD(kD), dt(dt)
{
    maxIntegralValue = -1;
    minOutput = -1;
    maxOutput = -1;
    reset();
}

void PID::update(float desiredValue, float currentValue) {
    lastlastError = lastError;
    lastError = currentError;
    currentError = desiredValue - currentValue;

    // Интегральная составляющая с защитой от переполнения
    integralValue += currentError * dt;
    if (maxIntegralValue > 0) {
        integralValue = constrain(integralValue, -maxIntegralValue, maxIntegralValue);
    }

    // Производная (метод Лагранжа 3-го порядка)
    if (dt > 1e-6) {
        dError = (currentError - lastError) / dt;  // упрощённая версия
        // Или ваша версия (требует 3 сохранённых ошибки):
        // dError = (lastlastError - 4.0*lastError + 3.0*currentError) / (2.0*dt);
    } else {
        dError = 0;
    }

    // Расчёт выхода
    unclippedOutput = kP * currentError + kI * integralValue + kD * dError;

    // Ограничение выхода
    if (minOutput != -1 && maxOutput != -1) {
        output = constrain(unclippedOutput, minOutput, maxOutput);
    } else {
        output = unclippedOutput;
    }

    // Anti-windup: если выход ограничен, не накапливаем интеграл
    if ((output <= minOutput && currentError > 0) || 
        (output >= maxOutput && currentError < 0)) {
        integralValue -= currentError * dt;  // откатываем интеграл
    }
}

void PID::reset() {
    integralValue = 0.0;
    currentError = 0.0;
    lastError = 0.0;
    lastlastError = 0.0;
    dError = 0.0;
    unclippedOutput = 0.0;
    output = 0.0;
}

void PID::setOutputLimits(float min, float max) {
    if (max > min) {
        minOutput = min;
        maxOutput = max;
    }
}

void PID::setMaxIntegralValue(float imaxIntegralValue) {
    if (imaxIntegralValue > 0.0) {
        maxIntegralValue = imaxIntegralValue;
    }
}

void PID::setPidParams(float ikP, float ikI, float ikD) {
    if (ikP > 0.0) kP = ikP;
    if (ikI >= 0.0) kI = ikI;
    if (ikD >= 0.0) kD = ikD;
}