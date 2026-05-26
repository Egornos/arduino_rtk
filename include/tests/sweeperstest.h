#pragma once
#include <Arduino.h>
#include "Sweepers.h"

Sweepers sweepers(9, 10);

unsigned long lastCommand = 0;
int commandIndex = 0;
bool autoTest = true;

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("=== Sweepers Test ===");
    Serial.println("Commands:");
    Serial.println("  s - Start sweeping");
    Serial.println("  t - Stop (go to 0°)");
    Serial.println("  1 - Set angle 90°");
    Serial.println("  2 - Set angle 180°");
    Serial.println("  a - Toggle auto test mode");
    Serial.println("====================");
    
    sweepers.start_stop(false);
}

void loop() {
    sweepers.update();
    
    // Автотест (каждые 5 секунд, если включён)
    if (autoTest) {
        unsigned long now = millis();
        if (now - lastCommand >= 5000) {
            lastCommand = now;
            
            switch (commandIndex) {
                case 0:
                    Serial.println("[Auto] Starting sweep (0° ↔ 180°)");
                    sweepers.start_stop(true);
                    break;
                case 1:
                    Serial.println("[Auto] Stopping at 0°");
                    sweepers.start_stop(false);
                    break;
                case 2:
                    Serial.println("[Auto] Manual angle 0°");
                    sweepers.start_stop(false);
                    sweepers.update();  // чтобы сбросить угол
                    break;
                case 3:
                    Serial.println("[Auto] Manual angle 90°");
                    // Временно отключаем автообновление и ставим угол вручную
                    sweepers.start_stop(false);
                    for (int angle = 0; angle <= 90; angle += 5) {
                        sweepers.update();
                        delay(20);
                    }
                    break;
                case 4:
                    Serial.println("[Auto] Manual angle 180°");
                    for (int angle = 90; angle <= 180; angle += 5) {
                        sweepers.update();
                        delay(20);
                    }
                    break;
                case 5:
                    Serial.println("[Auto] Back to sweeping");
                    sweepers.start_stop(true);
                    break;
                default:
                    commandIndex = -1;
                    break;
            }
            commandIndex++;
        }
    }
    
    // Ручные команды из Serial
    if (Serial.available() > 0) {
        char c = Serial.read();
        while (Serial.available()) Serial.read(); // очистка буфера
        
        switch (c) {
            case 's':
                Serial.println("Start sweeping (0° ↔ 180°)");
                sweepers.start_stop(true);
                break;
            case 't':
                Serial.println("Stop, go to 0°");
                sweepers.start_stop(false);
                break;
            case '1':
                Serial.println("Set angle 90°");
                sweepers.start_stop(false);
                break;
            case '2':
                Serial.println("Set angle 180°");
                sweepers.start_stop(false);
                break;
            case 'a':
                autoTest = !autoTest;
                Serial.print("Auto test mode: ");
                Serial.println(autoTest ? "ON" : "OFF");
                if (autoTest) lastCommand = millis();
                break;
            default:
                Serial.println("Unknown command");
                break;
        }
    }
}