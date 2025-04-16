#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include <Arduino.h>

class Joystick {

    private :
        int xPin;
        int yPin;
        int swPin;

    public :
        Joystick(int xPin, int yPin, int swPin) : xPin(xPin), yPin(yPin), swPin(swPin) {
            pinMode(xPin, INPUT);
            pinMode(yPin, INPUT);
            pinMode(swPin, INPUT_PULLUP);
        }

        uint16_t getX() {
            return analogRead(xPin);
        }

        uint16_t getY() {
            return analogRead(yPin);
        }

        bool isPressed() {
            return digitalRead(swPin) == LOW;
        }
};

#endif // __JOYSTICK_H__