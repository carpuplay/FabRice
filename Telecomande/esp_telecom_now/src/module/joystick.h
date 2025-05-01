#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include <Arduino.h>

class Joystick {

    private :
        int xPin;
        int yPin;
        int swPin;

        ADS1015 ads;

    public :
        Joystick(int xPin, int yPin, int swPin, ADS1015& ads) : xPin(xPin), yPin(yPin), swPin(swPin), ads(ads) {
            pinMode(swPin, INPUT_PULLUP);
        }

        uint16_t getX() {
            return ads.readADC(xPin);
        }

        uint16_t getY() {
            return ads.readADC(yPin);
        }

        bool isPressed() {
            return digitalRead(swPin) == LOW;
        }
};

#endif // __JOYSTICK_H__