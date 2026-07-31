#pragma once

class BlinkingLed {
public:
    BlinkingLed(byte pin) : pin(pin) {
    }

    void setup() {
        pinMode(pin, OUTPUT);
    }

    void setOn(unsigned long time) {
        state = true;
        endTime = time + blinkTime;
        digitalWrite(pin, HIGH);
    }

    void loop(unsigned long time) {
        if ((time >= endTime) && state) {
            state = false;
            digitalWrite(pin, LOW);
        }
    }

private:
    byte pin = 0;
    bool state = false;
    unsigned long endTime = 0;
    static const unsigned long blinkTime = 100;
};