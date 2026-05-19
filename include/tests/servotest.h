#include <Arduino.h>
#include <Servo.h>

Servo testServo;

void setup() {
  Serial.begin(115200);  // ← изменил на 115200
  
  Serial.println("Try pin 9...");
  testServo.attach(9);
  testServo.write(90);
  delay(1000);
  testServo.detach();
  
  Serial.println("Try pin 10...");
  testServo.attach(10);
  testServo.write(90);
  delay(1000);
  testServo.detach();
  
  Serial.println("Try pin 11...");
  testServo.attach(11);
  testServo.write(90);
  delay(1000);
  testServo.detach();
  
  Serial.println("Try pin 12...");
  testServo.attach(12);
  testServo.write(90);
  delay(1000);
  testServo.detach();
  
  Serial.println("Тест завершён. На каком пине серво повернулось?");
}

void loop() {}