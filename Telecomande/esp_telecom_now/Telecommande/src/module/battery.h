#ifndef __BATTERY_H__
#define __BATTERY_H__

#include <Arduino.h>

class Battery {
    private:
        int pin;
        float voltage;
        float maxVoltage;
        float r1;
        float r2;
        float vRef;
        int ADC_MAX = 4095; // ADC max value for ESP32

    public:
        Battery (int pin, float maxVoltage, float r1, float r2, float vRef) 
            : pin(pin), maxVoltage(maxVoltage), r1(r1), r2(r2), vRef(vRef) {
            pinMode(pin, INPUT);
        }

        float readVoltage() {
            int rawValue = analogRead(pin);
            voltage = (rawValue / (float)ADC_MAX) * vRef;
            return voltage * (r1 + r2) / r2;
        }

        float getBatteryPercentage(float voltage) {
            return (voltage / maxVoltage) * 100;
        }
};

#endif // __BATTERY_H__