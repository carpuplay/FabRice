#ifndef __BUZZER_H__
#define __BUZZER_H__

#include <Arduino.h>

class Buzzer {
    private :
        int pin;
    
    public :
        Buzzer(int pin) : pin(pin) {
            pinMode(pin, OUTPUT);
            digitalWrite(pin, LOW); // Initialize buzzer to off
        }

        void beep(int duration) {
            digitalWrite(pin, HIGH);
            delay(duration);
            digitalWrite(pin, LOW);
        }

        void multipleBeeps(int count, int duration, int pause = 0) {
            for (int i = 0; i < count; i++) {
                beep(duration);
                delay(pause); // Delay between beeps
            }
        }
};

#endif // __BUZZER_H__