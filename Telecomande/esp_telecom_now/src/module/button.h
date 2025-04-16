#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <Arduino.h>

class Button {
    private :
        int pin
    
    public :
        Button(int pin) : pin(pin) {
            pinMode(pin, INPUT_PULLUP);
        }

        bool isPressed() {
            return digitalRead(pin) == LOW;
        }
}

#endif // __BUTTON_H__