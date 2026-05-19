#include <Arduino.h>

float targetLeft = 0.0;
float targetRight = 0.0;
bool sweepers_is_active = false;

int readBuffer(String &buffer) {
    int commaIndex = buffer.indexOf(',');
    if(buffer.length() == 0) return -1;
    if(commaIndex == -1) {
        sweepers_is_active = buffer.toInt();
        return 0;
    }
    else {
        String leftStr = buffer.substring(0, commaIndex);
        String rightStr = buffer.substring(commaIndex + 1);
        if(leftStr.length() == 0 || rightStr.length() == 0) return -1;

        targetLeft = leftStr.toFloat();
        targetRight = rightStr.toFloat();
        return 1;
    }

    return -1;
}
String buffer = "";

void readSerialData() {

    while(Serial.available()) {
        char c = Serial.read();
        if(c == '\n') {
            if(readBuffer(buffer) == -1) Serial.print("Error input data.");
            buffer = "";
        }
        else if(c != '\r'){
            buffer += c;
            if(buffer.length() >= 30) buffer = "";
        }
    }
}