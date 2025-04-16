#ifndef __LED_H__
#define __LED_H__

#include <Arduino.h>

class Led {
    private : 
        int pin;
    
    public : 
        Led(int pin) : pin(pin) {
            pinMode(pin, OUTPUT);
            digitalWrite(pin, LOW);
        }

        void on() {
            digitalWrite(pin, HIGH);
        }

        void off() {
            digitalWrite(pin, LOW);
        }

        void blink(int duration) {
            on();
            delay(duration);
            off();
        }
}

#endif // __LED_H__